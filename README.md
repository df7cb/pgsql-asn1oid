asn1oid Type for PostgreSQL
===========================

[![Build Status](https://travis-ci.org/ChristophBerg/pgsql-asn1oid.svg?branch=master)](https://travis-ci.org/ChristophBerg/pgsql-asn1oid)

The asn1oid extension provides a datatype for ASN.1 OIDs in PostgreSQL.

```
CREATE EXTENSION asn1oid;

# SELECT '1.3.6.1.4.1'::asn1oid;
   asn1oid
─────────────
 1.3.6.1.4.1
```

Author, Copyright and License
-----------------------------

Simon Richter <Simon.Richter@hogyros.de>

Copyright (C) 2010 Simon Richter

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This package is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
