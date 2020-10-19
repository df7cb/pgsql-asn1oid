MODULES = asn1oid
EXTENSION = asn1oid
DATA = asn1oid--1.sql
REGRESS = init asn1oid

PG_CONFIG := pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)

include $(PGXS)
