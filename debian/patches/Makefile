--- a/Makefile
+++ b/Makefile
@@ -1,7 +1,8 @@
 MODULES = asn1oid
+DATA = asn1oid.sql
+REGRESS = init asn1oid
 
-PGCONFIG = pg_config
-
-PGXS = $(shell $(PGCONFIG) --pgxs)
+PG_CONFIG := pg_config
+PGXS := $(shell $(PG_CONFIG) --pgxs)
 
 include $(PGXS)
--- a/asn1oid.sql
+++ b/asn1oid.sql
@@ -3,13 +3,13 @@ CREATE FUNCTION asn1oid_input (cstring)
     RETURNS asn1oid
     IMMUTABLE
     STRICT
-    LANGUAGE 'C'
+    LANGUAGE C
     AS 'asn1oid.so','asn1oid_input';
 CREATE FUNCTION asn1oid_output (asn1oid)
     RETURNS cstring
     IMMUTABLE
     STRICT
-    LANGUAGE 'C'
+    LANGUAGE C
     AS 'asn1oid.so','asn1oid_output';
 CREATE TYPE asn1oid (
     INPUT = asn1oid_input,
@@ -18,43 +18,43 @@ CREATE FUNCTION asn1oid_eq (asn1oid, asn
     RETURNS bool
     IMMUTABLE
     STRICT
-    LANGUAGE 'C'
+    LANGUAGE C
     AS 'asn1oid.so','asn1oid_eq';
 CREATE FUNCTION asn1oid_ne (asn1oid, asn1oid)
     RETURNS bool
     IMMUTABLE
     STRICT
-    LANGUAGE 'C'
+    LANGUAGE C
     AS 'asn1oid.so','asn1oid_ne';
 CREATE FUNCTION asn1oid_lt (asn1oid, asn1oid)
     RETURNS bool
     IMMUTABLE
     STRICT
-    LANGUAGE 'C'
+    LANGUAGE C
     AS 'asn1oid.so','asn1oid_lt';
 CREATE FUNCTION asn1oid_gt (asn1oid, asn1oid)
     RETURNS bool
     IMMUTABLE
     STRICT
-    LANGUAGE 'C'
+    LANGUAGE C
     AS 'asn1oid.so','asn1oid_gt';
 CREATE FUNCTION asn1oid_le (asn1oid, asn1oid)
     RETURNS bool
     IMMUTABLE
     STRICT
-    LANGUAGE 'C'
+    LANGUAGE C
     AS 'asn1oid.so','asn1oid_le';
 CREATE FUNCTION asn1oid_ge (asn1oid, asn1oid)
     RETURNS bool
     IMMUTABLE
     STRICT
-    LANGUAGE 'C'
+    LANGUAGE C
     AS 'asn1oid.so','asn1oid_ge';
 CREATE FUNCTION asn1oid_cmp (asn1oid, asn1oid)
     RETURNS int4
     IMMUTABLE
     STRICT
-    AS 'asn1oid.so','asn1oid_cmp' LANGUAGE 'C';
+    AS 'asn1oid.so','asn1oid_cmp' LANGUAGE C;
 CREATE OPERATOR = (
     LEFTARG = asn1oid,
     RIGHTARG = asn1oid,
--- /dev/null
+++ b/expected/asn1oid.out
@@ -0,0 +1,6 @@
+SELECT '1.2.3'::asn1oid;
+ asn1oid 
+---------
+ 1.2.3
+(1 row)
+
--- /dev/null
+++ b/expected/init.out
@@ -0,0 +1 @@
+\set ECHO off
--- /dev/null
+++ b/sql/asn1oid.sql
@@ -0,0 +1 @@
+SELECT '1.2.3'::asn1oid;
--- /dev/null
+++ b/sql/init.sql
@@ -0,0 +1,3 @@
+\set ECHO off
+set client_min_messages = warning;
+\i asn1oid.sql
