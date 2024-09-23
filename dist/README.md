<div id="top" align="center">
<h1>dist folder</h1>

<p>`dist` folder of `qt_files_photo-gallery`</p>

</div>

<hr>

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**

- [Description](#description)
- [example ini-file](#example-ini-file)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

<hr>

# Description

The `dist` folder provides tools, apps and example config-files

# example ini-file

Example Ini-file _qt_files_photo-gallery.ini_ for `qt_files_photo-gallery`

```Ini
[SQL_dev]
rdbms=postgresql          # only pg is supported yet
dbname=photo_gallery      # <my database>
hostname=rdbms_srv        # <database server> // IP-Address or FQDN
password=Top_Secret!      # <database user password>
port=8154                 # <database server port>
username=photo_rw_user    # <database user>

[SQL_int]
rdbms=
dbname=
hostname=
password=
port=
username=

[SQL_prod]
rdbms=
dbname=
hostname=
password=
port=
username=

[APP_dev]
Logifle=./qt_files_photo.log                # <path/to/logfile> qt_files_photo-gallery
write_to_db=false                           # true | false // true: insert vals into DB | false: write sql inserts into file
write_sql_to_file=./qt_files_photo.sql      # <path/to/file.sql>

[APP_int]
Logifle=
write_to_db=
write_sql_to_file=

[APP_prod]
Logifle=
write_to_db=
write_sql_to_file=
```