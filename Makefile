MODULES = asn1oid

PGCONFIG = pg_config

PGXS = $(shell $(PGCONFIG) --pgxs)

include $(PGXS)
