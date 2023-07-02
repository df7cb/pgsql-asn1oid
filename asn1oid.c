#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <postgres.h>
#include <fmgr.h>
#if PG_VERSION_NUM >= 160000
#include <varatt.h>
#endif

PG_MODULE_MAGIC;

Datum asn1oid_input(PG_FUNCTION_ARGS);
Datum asn1oid_output(PG_FUNCTION_ARGS);

Datum asn1oid_eq(PG_FUNCTION_ARGS);
Datum asn1oid_ne(PG_FUNCTION_ARGS);
Datum asn1oid_lt(PG_FUNCTION_ARGS);
Datum asn1oid_gt(PG_FUNCTION_ARGS);
Datum asn1oid_le(PG_FUNCTION_ARGS);
Datum asn1oid_ge(PG_FUNCTION_ARGS);
Datum asn1oid_cmp(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(asn1oid_input);
PG_FUNCTION_INFO_V1(asn1oid_output);
PG_FUNCTION_INFO_V1(asn1oid_eq);
PG_FUNCTION_INFO_V1(asn1oid_ne);
PG_FUNCTION_INFO_V1(asn1oid_lt);
PG_FUNCTION_INFO_V1(asn1oid_gt);
PG_FUNCTION_INFO_V1(asn1oid_le);
PG_FUNCTION_INFO_V1(asn1oid_ge);
PG_FUNCTION_INFO_V1(asn1oid_cmp);

struct asn1oid
{
    int32   vl_len_;
    uint32   data[1];
};

typedef struct asn1oid asn1oid;

static unsigned int size(asn1oid const *oid)
{
    return (VARSIZE(oid) - offsetof(asn1oid, data)) / sizeof(uint32);
}

#define PG_GETARG_ASN1OID(x) ((asn1oid *) PG_DETOAST_DATUM(PG_GETARG_DATUM(x)))

Datum asn1oid_input(PG_FUNCTION_ARGS)
{
    char *str = PG_GETARG_CSTRING(0);

    uint32 tmp[64];
    unsigned int i, j;
    char const *c;
    unsigned int size;
    asn1oid *ret;

    i = 0;

    tmp[i] = 0;

    for(c = str; *c; ++c)
    {
        switch(*c)
        {
        case '0':
            tmp[i] *= 10;
            break;
        case '1':
            tmp[i] *= 10;
            tmp[i] += 1;
            break;
        case '2':
            tmp[i] *= 10;
            tmp[i] += 2;
            break;
        case '3':
            tmp[i] *= 10;
            tmp[i] += 3;
            break;
        case '4':
            tmp[i] *= 10;
            tmp[i] += 4;
            break;
        case '5':
            tmp[i] *= 10;
            tmp[i] += 5;
            break;
        case '6':
            tmp[i] *= 10;
            tmp[i] += 6;
            break;
        case '7':
            tmp[i] *= 10;
            tmp[i] += 7;
            break;
        case '8':
            tmp[i] *= 10;
            tmp[i] += 8;
            break;
        case '9':
            tmp[i] *= 10;
            tmp[i] += 9;
            break;
        case '.':
            if(c == str) {
                if (c[1]) {
                    /* Skip over first dot */
                    break;
                }
                ereport(ERROR,
                  (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                  errmsg("invalid input syntax for type asn1oid: \"%s\"",
                    str)));
            }
            ++i;
            if(i >= 64)
                ereport(ERROR,
                  (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                  errmsg("invalid input syntax for type asn1oid: \"%s\"",
                    str)));
            tmp[i] = 0;
            break;
        default:
            ereport(ERROR,
              (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
              errmsg("invalid input syntax for type asn1oid: \"%s\"",
                str)));
        }
    }
    if(c == str || c[-1] == '.')
        ereport(ERROR,
          (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
          errmsg("invalid input syntax for type asn1oid: \"%s\"",
            str)));

    ++i;

    size = offsetof(asn1oid, data) + sizeof(uint32) * i;

    ret = palloc(size);

    SET_VARSIZE(ret, size);

    for(j = 0; j < i; ++j)
        ret->data[j] = tmp[j];

    PG_RETURN_POINTER(ret);
}

Datum asn1oid_output(PG_FUNCTION_ARGS)
{
    asn1oid *oid = PG_GETARG_ASN1OID(0);

    unsigned int len = size(oid);

    unsigned int size = 0;

    unsigned int i;

    char *ret, *j;

    if(len == 0)
        PG_RETURN_NULL();

    for(i = 0; i < len; ++i)
    {
        uint32 t = oid->data[i];
        if(t < 10)
            size += 2;
        else if(t < 100)
            size += 3;
        else if(t < 1000)
            size += 4;
        else if(t < 10000)
            size += 5;
        else if(t < 100000)
            size += 6;
        else if(t < 1000000)
            size += 7;
        else if(t < 10000000)
            size += 8;
        else if(t < 100000000)
            size += 9;
        else if(t < 1000000000)
            size += 10;
        else
            size += 11;
    }

    ret = palloc(size);

    j = ret;

    for(i = 0; i < len; ++i)
    {
        uint32 t = oid->data[i];

        char *b = j;
        char *r;

        do
        {
            *j++ = '0' + t % 10;
            t /= 10;
        }
        while(t);

        r = j;

        for(--r; b < r; ++b, --r)
        {
            char t = *r;
            *r = *b;
            *b = t;
        }

        *j++ = '.';
    }

    j[-1] = 0;

    PG_FREE_IF_COPY(oid, 0);
    PG_RETURN_CSTRING(ret);
}

static int cmp(asn1oid const *lhs, asn1oid const *rhs)
{
    unsigned int lhs_size = size(lhs);
    unsigned int rhs_size = size(rhs);

    unsigned int size = (lhs_size < rhs_size)?lhs_size:rhs_size;

    unsigned int i;

    for(i = 0; i < size; ++i)
    {
        uint32 l = lhs->data[i];
        uint32 r = rhs->data[i];
        if(l < r)
            return -1;
        if(l > r)
            return 1;
    }
    if(lhs_size < rhs_size)
        return -1;
    if(lhs_size > rhs_size)
        return 1;
    return 0;
}

Datum asn1oid_eq(PG_FUNCTION_ARGS)
{
    asn1oid *lhs = PG_GETARG_ASN1OID(0);
    asn1oid *rhs = PG_GETARG_ASN1OID(1);

    int res = cmp(lhs, rhs);

    PG_FREE_IF_COPY(lhs, 0);
    PG_FREE_IF_COPY(rhs, 1);
    PG_RETURN_BOOL(res == 0);
}

Datum asn1oid_ne(PG_FUNCTION_ARGS)
{
    asn1oid *lhs = PG_GETARG_ASN1OID(0);
    asn1oid *rhs = PG_GETARG_ASN1OID(1);

    int res = cmp(lhs, rhs);

    PG_FREE_IF_COPY(lhs, 0);
    PG_FREE_IF_COPY(rhs, 1);
    PG_RETURN_BOOL(res != 0);
}

Datum asn1oid_lt(PG_FUNCTION_ARGS)
{
    asn1oid *lhs = PG_GETARG_ASN1OID(0);
    asn1oid *rhs = PG_GETARG_ASN1OID(1);

    int res = cmp(lhs, rhs);

    PG_FREE_IF_COPY(lhs, 0);
    PG_FREE_IF_COPY(rhs, 1);
    PG_RETURN_BOOL(res < 0);
}

Datum asn1oid_gt(PG_FUNCTION_ARGS)
{
    asn1oid *lhs = PG_GETARG_ASN1OID(0);
    asn1oid *rhs = PG_GETARG_ASN1OID(1);

    int res = cmp(lhs, rhs);

    PG_FREE_IF_COPY(lhs, 0);
    PG_FREE_IF_COPY(rhs, 1);
    PG_RETURN_BOOL(res > 0);
}

Datum asn1oid_le(PG_FUNCTION_ARGS)
{
    asn1oid *lhs = PG_GETARG_ASN1OID(0);
    asn1oid *rhs = PG_GETARG_ASN1OID(1);

    int res = cmp(lhs, rhs);

    PG_FREE_IF_COPY(lhs, 0);
    PG_FREE_IF_COPY(rhs, 1);
    PG_RETURN_BOOL(res <= 0);
}

Datum asn1oid_ge(PG_FUNCTION_ARGS)
{
    asn1oid *lhs = PG_GETARG_ASN1OID(0);
    asn1oid *rhs = PG_GETARG_ASN1OID(1);

    int res = cmp(lhs, rhs);

    PG_FREE_IF_COPY(lhs, 0);
    PG_FREE_IF_COPY(rhs, 1);
    PG_RETURN_BOOL(res >= 0);
}

Datum asn1oid_cmp(PG_FUNCTION_ARGS)
{
    asn1oid *lhs = PG_GETARG_ASN1OID(0);
    asn1oid *rhs = PG_GETARG_ASN1OID(1);

    int res = cmp(lhs, rhs);

    PG_FREE_IF_COPY(lhs, 0);
    PG_FREE_IF_COPY(rhs, 1);
    PG_RETURN_INT32(res);
}
