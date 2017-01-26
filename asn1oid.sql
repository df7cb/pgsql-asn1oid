CREATE TYPE asn1oid;
CREATE FUNCTION asn1oid_input (cstring)
    RETURNS asn1oid
    IMMUTABLE
    STRICT
    LANGUAGE 'C'
    AS 'asn1oid.so','asn1oid_input';
CREATE FUNCTION asn1oid_output (asn1oid)
    RETURNS cstring
    IMMUTABLE
    STRICT
    LANGUAGE 'C'
    AS 'asn1oid.so','asn1oid_output';
CREATE TYPE asn1oid (
    INPUT = asn1oid_input,
    OUTPUT = asn1oid_output);
CREATE FUNCTION asn1oid_eq (asn1oid, asn1oid)
    RETURNS bool
    IMMUTABLE
    STRICT
    LANGUAGE 'C'
    AS 'asn1oid.so','asn1oid_eq';
CREATE FUNCTION asn1oid_ne (asn1oid, asn1oid)
    RETURNS bool
    IMMUTABLE
    STRICT
    LANGUAGE 'C'
    AS 'asn1oid.so','asn1oid_ne';
CREATE FUNCTION asn1oid_lt (asn1oid, asn1oid)
    RETURNS bool
    IMMUTABLE
    STRICT
    LANGUAGE 'C'
    AS 'asn1oid.so','asn1oid_lt';
CREATE FUNCTION asn1oid_gt (asn1oid, asn1oid)
    RETURNS bool
    IMMUTABLE
    STRICT
    LANGUAGE 'C'
    AS 'asn1oid.so','asn1oid_gt';
CREATE FUNCTION asn1oid_le (asn1oid, asn1oid)
    RETURNS bool
    IMMUTABLE
    STRICT
    LANGUAGE 'C'
    AS 'asn1oid.so','asn1oid_le';
CREATE FUNCTION asn1oid_ge (asn1oid, asn1oid)
    RETURNS bool
    IMMUTABLE
    STRICT
    LANGUAGE 'C'
    AS 'asn1oid.so','asn1oid_ge';
CREATE FUNCTION asn1oid_cmp (asn1oid, asn1oid)
    RETURNS int4
    IMMUTABLE
    STRICT
    AS 'asn1oid.so','asn1oid_cmp' LANGUAGE 'C';
CREATE OPERATOR = (
    LEFTARG = asn1oid,
    RIGHTARG = asn1oid,
    PROCEDURE = asn1oid_eq,
    COMMUTATOR = '=',
    NEGATOR = '<>',
    RESTRICT = eqsel,
    JOIN = eqjoinsel,
    HASHES,
    MERGES);
CREATE OPERATOR < (
    LEFTARG = asn1oid,
    RIGHTARG = asn1oid,
    PROCEDURE = asn1oid_lt,
    COMMUTATOR = '>',
    NEGATOR = '>=',
    RESTRICT = scalarltsel,
    JOIN = scalarltjoinsel);
CREATE OPERATOR > (
    LEFTARG = asn1oid,
    RIGHTARG = asn1oid,
    PROCEDURE = asn1oid_gt,
    COMMUTATOR = '<',
    NEGATOR = '<=',
    RESTRICT = scalargtsel,
    JOIN = scalargtjoinsel);
CREATE OPERATOR <= (
    LEFTARG = asn1oid,
    RIGHTARG = asn1oid,
    PROCEDURE = asn1oid_le,
    COMMUTATOR = '>=',
    NEGATOR = '>',
    RESTRICT = scalarltsel,
    JOIN = scalarltjoinsel);
CREATE OPERATOR >= (
    LEFTARG = asn1oid,
    RIGHTARG = asn1oid,
    PROCEDURE = asn1oid_ge,
    COMMUTATOR = '<=',
    NEGATOR = '<',
    RESTRICT = scalargtsel,
    JOIN = scalargtjoinsel);
CREATE OPERATOR <> (
    LEFTARG = asn1oid,
    RIGHTARG = asn1oid,
    PROCEDURE = asn1oid_ne,
    COMMUTATOR = '<>',
    NEGATOR = '=',
    RESTRICT = neqsel,
    JOIN = neqjoinsel);
CREATE OPERATOR CLASS asn1oid_ops
    DEFAULT FOR TYPE asn1oid
    USING btree AS
        OPERATOR 1 <,
        OPERATOR 2 <=,
        OPERATOR 3 =,
        OPERATOR 4 >=,
        OPERATOR 5 >,
        FUNCTION 1 asn1oid_cmp(asn1oid, asn1oid);
