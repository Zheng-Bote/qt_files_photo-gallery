<div id="top" align="center">
<h1>qt_files_photo-gallery</h1>

<p>QT6 CXX20 console app to add photos to Database</p>

[Report Issue](https://github.com/Zheng-Bote/qt_files_photo-gallery/issues) [Request Feature](https://github.com/Zheng-Bote/qt_files_photo-gallery/pulls)

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)
![GitHub Created At](https://img.shields.io/github/created-at/Zheng-Bote/qt_files_photo-gallery)

</div>

<hr>

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->

**Table of Contents**

- [Description](#description)
  - [Features](#features)
  - [Status](#status)
    - [Application / Tool](#application--tool)
    - [Documentation](#documentation)
      - [README](#readme)
      - [other Markdown files](#other-markdown-files)
- [Installation](#installation)
  - [Dependencies](#dependencies)
    - [QT](#qt)
    - [cxxopts](#cxxopts)
    - [inifile-cpp](#inifile-cpp)
    - [plog](#plog)
  - [folder structure](#folder-structure)
  - [Build](#build)
    - [QT6](#qt6)
    - [manually](#manually)
      - [Linux, macOS](#linux-macos)
- [API Reference](#api-reference)
  - [Inputs / Parameters](#inputs--parameters)
  - [Outputs](#outputs)
  - [Usage/Examples/Tests](#usageexamplestests)
- [Documentation](#documentation-1)
  - [Architecture](#architecture)
    - [Github](#github)
      - [Github Repo](#github-repo)
      - [Github Actions / Workflows](#github-actions--workflows)
  - [Application](#application)
    - [bounded context](#bounded-context)
    - [data import](#data-import)
  - [Inifile](#inifile)
  - [DevOps](#devops)
    - [Software Bill of Materials (SBoM)](#software-bill-of-materials-sbom)
  - [Github Page](#github-page)
  - [Github Wiki](#github-wiki)
  - [Comments](#comments)
  - [Screenshots](#screenshots)
- [Authors and License](#authors-and-license)
  - [License](#license)
  - [Authors](#authors)
    - [Code Contributors](#code-contributors)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

<hr>

# Description

![QT](https://img.shields.io/badge/Community-6-41CD52?logo=qt)
![CXX](https://img.shields.io/badge/C++-20-blue?logo=cplusplus)

QT6 CXX20 console app to add photos to Database

### Features

- [x] supports PostgreSQL (insert)
- [x] supports SQLite3 (incl. create tables, indexes, triggers; insert)
- [x] supports exports to SQL-file ("native", system-independent SQL; insert)
- [x] Exchangeable Image File Format (Exif; read, write; sql insert)
- [x] IPTC-IIM (IPTC; read, write; sql insert)
- [ ] converts images to several WebP sizes
- [ ] advanced-extra-super-ultra-special feature xyz

<br>

- [x] OSS and license
- [x] works as designed
- [ ] no bugs

<br>

- [x] some more or less usefull Github Actions for GH-repo, GH-pages, GH-wiki, CI/CD-Pipelines, Release-Mgmt.
- [x] Packaging: Conan
- [x] Buildsystem: CMake
- [ ] Installer:
- [ ] portable application / runtime binaries (see Release)
- [x] SBOM included (static; also Linux shell commands; GH-Action in work)
- [ ] separation of documentation (general Readme - detailed `/docs/*`)

<br>

- [ ] runs on DOS/Windows
- [ ] runs on MacOS
- [x] runs on Linux
- [ ] runs on iOS
- [ ] runs on Android
- [ ] runs on HarmonyOS

<p align="right">(<a href="#top">back to top</a>)</p>

## Status

### Application / Tool

![Status](https://img.shields.io/badge/Status-under_construction-red)

![GitHub Issues](https://img.shields.io/github/issues/Zheng-Bote/qt_files_photo-gallery)
![GitHub Pull Requests](https://img.shields.io/github/issues-pr/Zheng-Bote/qt_files_photo-gallery)

### Documentation

_see also:_ [Application Documentation](#documentation)

#### README

[![Repo - create Repo-Tree in README.md](https://github.com/Zheng-Bote/qt_files_photo-gallery/actions/workflows/repo-create_tree_readme.yml/badge.svg)](https://github.com/Zheng-Bote/qt_files_photo-gallery/actions/workflows/repo-create_tree_readme.yml)

[![Repo - update Readme](https://github.com/Zheng-Bote/qt_files_photo-gallery/actions/workflows/repo-call_Readme.yml/badge.svg)](https://github.com/Zheng-Bote/qt_files_photo-gallery/actions/workflows/repo-call_Readme.yml)

#### other Markdown files

[![Repo - create TOC of Markdown files](https://github.com/Zheng-Bote/qt_files_photo-gallery/actions/workflows/repo-create_doctoc_md.yml/badge.svg)](https://github.com/Zheng-Bote/qt_files_photo-gallery/actions/workflows/repo-create_doctoc_md.yml)

create ToC in Markdown files in folders

- .github/actions/\*\*
- .github/workflows/\*\*
- dist/\*\*
- docs/\*\*

<p align="right">(<a href="#top">back to top</a>)</p>

# Installation

bla bla ... everything easy and green with No Code/Low code and without any costs

## Dependencies

#### QT

_QT6 - Community Edition_

The Qt framework contains a comprehensive set of highly intuitive and modularized C++ library classes and is loaded with APIs to simplify your application development. Qt produces highly readable, easily maintainable and reusable code with high runtime performance and small footprint – and it's cross-platform.

[![QT](https://img.shields.io/badge/Community-for_Open_Source_Development-black?logo=qt)](https://www.qt.io/download-open-source)
[![LGPL](https://img.shields.io/badge/License-LGPL_v3-green.svg)](https://choosealicense.com/licenses/lgpl-3.0/) _see also:_[Obligations of the GPL and LGPL](https://www.qt.io/licensing/open-source-lgpl-obligations)

#### cxxopts

a lightweight C++ option parser library, supporting the standard GNU style syntax for options.

[![jarro2783](https://img.shields.io/badge/Github-jarro2783-black?logo=github)](https://github.com/jarro2783/cxxopts)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

> \[!NOTE]
> managed via the package manager

#### inifile-cpp

inifile-cpp is a simple and easy to use single header-only ini file en- and decoder for C++.

[![Fabian Meyer](https://img.shields.io/badge/Github-Fabian_Meyer-black?logo=github)](https://github.com/Rookfighter/inifile-cpp)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

> \[!NOTE]
> included in `src/includes`

#### plog

Plog - portable, simple and extensible C++ logging library

[![Sergey Podobry](https://img.shields.io/badge/Github-Sergey_Podobry-black?logo=github)](https://github.com/SergiusTheBest/plog)
[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

> \[!NOTE]
> managed via the package manager

## folder structure

<!-- readme-tree start -->

```
.
├── .github
│   ├── actions
│   │   └── doctoc
│   │       ├── README.md
│   │       ├── action.yml
│   │       └── dist
│   │           ├── index.js
│   │           ├── index.js.map
│   │           ├── licenses.txt
│   │           └── sourcemap-register.js
│   └── workflows
│       ├── repo-actions_docu.yml
│       ├── repo-call_Readme.yml
│       ├── repo-create_doctoc.yml_
│       ├── repo-create_doctoc_md.yml
│       ├── repo-create_tree_readme.yml
│       └── repo-test_sbom.yml
├── .gitignore
├── LICENSE
├── README.md
├── dist
│   ├── README.md
│   ├── atom_usages_v0.1.0.json
│   ├── qt_files_photo-gallery.ini
│   └── sbom_v0.1.0.json
├── src
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   │   └── cmake.check_cache
│   ├── CMakeLists.txt
│   ├── conanfile.py
│   ├── conanfile.txt
│   ├── includes
│   │   ├── inicpp.h
│   │   ├── rz_inifile.cpp
│   │   ├── rz_inifile.h
│   │   ├── rz_pg_db.cpp
│   │   ├── rz_pg_db.h
│   │   ├── rz_readdir.cpp
│   │   ├── rz_readdir.h
│   │   ├── rz_sqlite3_db.cpp
│   │   └── rz_sqlite3_db.h
│   └── main.cpp
└── tree.bak

9 directories, 35 files
```

<!-- readme-tree end -->

## Build

### QT

_QT6_

just load the project in QT Creator and run build <debug> or <release...>

### manually

#### Linux, macOS

```Bash
cd src

conan install . --output-folder=../build --build=missing

cd ../build

cmake -S ../src -B . -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake  -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE=Release

cmake --build .
```

<p align="right">(<a href="#top">back to top</a>)</p>

# API Reference

> \[!IMPORTANT]
> still under construction.

## Inputs / Parameters

> [!NOTE]
> at least 1 parameter is required

- `-a` or `-i <path to>/<ini file>`

> [!TIP]
> use shortcuts

- use `-a` for shortcut
- use `-a -e <env>` for shortcut
- use `-i <path to>/<ini file>`
- use `-i <path to>/<ini file> -e <env>`

> \[!IMPORTANT]
> still under construction.

| Parameter      | Type     | Description                                                                               |
| :------------- | :------- | :---------------------------------------------------------------------------------------- |
| `-a --auto`    | `none`   | _Optional:_ load Ini `<program path>/<program>.ini>`                                      |
| `-c --create`  | `string` | _Optional:_ create Ini `<path to>/<file.ini>` or default: `<program path>/<program>.ini>` |
| `-e --env`     | `string` | _Optional:_ `<dev> , <ini> , <prod>`or default:`dev`                                      |
| `-i --ini`     | `string` | _Optional:_ `<pathTo/inifile>`                                                            |
| `-l --listini` | `string` | _Optional:_ `<pathTo/inifile>` or default: `<program path>/<program>.ini>`                |
| `-v --version` | `none`   | _Optional:_ `<program>-<major>.<minor>.<patch>`                                           |
| `-h --help`    | `none`   | _Optional:_ list help menu                                                                |

## Outputs

- `exit(EXIT_SUCCESS)` or `exit(EXIT_FAILURE)`

- PostgreSQL: inserted rows
- SQLite3: created tables, indexes, triggers; inserted rows
- SQL-File: created file with sql inserts

```mermaid
flowchart TD;
A[[program]] --> S[["`**Storage**
./Webp/..`"]]
S[Storage] & D[Database] --> F(EXIT_SUCCESS)
S[Storage] & E[SQL File] --> F(EXIT_SUCCESS)
S ---->|error| G(EXIT_FAILURE)
```

<p align="right">(<a href="#top">back to top</a>)</p>

## Usage/Examples/Tests

> [!NOTE]
> at least 1 parameter is required:
> `-a` or `-i <path to>/<ini file>`

> [!TIP]
> use `-a` for shortcut
> use `-a -e <env>` for shortcut
> use `-i <path to>/<ini file>`
> use `-i <path to>/<ini file> -e <env>`

<p align="right">(<a href="#top">back to top</a>)</p>

# Documentation

see also: <https://linktodocumentation>

## Architecture

### Github

#### Github Repo

```mermaid
block-beta
  columns 4
  Repo:4
  block:group1:1
    columns 1
    id0[".github"]
    block:group2:1
      columns 1
      id1[["workflows"]]
      id2[["actions"]]
    end
  end
  docs dist src
  block:group3:4
    %% columns auto (default)
    A["gh-pages"] B["gh-wiki"]
  end
```

#### Github Actions / Workflows

```mermaid
flowchart TD;
    A[Workflow]-. parameter .->B[[callable Workflow]]
    B-- parameter -->C[Action]
    C-->D(README)

    A[Workflow]-. parameter .->E[[callable Workflow]]
    E-- parameter -->F[Action]
    F-->J(Markdown files)

    A[Workflow]-->K[[Workflow]]
    K-->L[Action]
    L-->M("GH-Pages")

    A[Workflow]-->N[[Workflow]]
    N-->O[Action]
    O-->P("GH-Wiki")
```

<p align="right">(<a href="#top">back to top</a>)</p>

## Application

### bounded context

- Webserver NGinx
- Appserver (Applicationserver) Rust Rocket
- Database PostgreSQL
- Storage (for Webserver static content as well as for Appserver Photo-Gallery management)

```mermaid
architecture-beta
    group bounded_context(cloud)[Photo Gallery]

    service server1(server)[Webserver] in bounded_context
    service server2(server)[Appserver] in bounded_context
    service db(database)[Database] in bounded_context
    service disk1(disk)[Storage] in bounded_context
    service disk2(disk)[Storage] in bounded_context

    server1:T -- B:server2
    server2:T -- B:db
    disk2:L -- R:server2
    disk1:L -- R:server1
```

### data import

- collecting local files
- read attributes (size, geometry)
- read Exif/IPTC (if present)
- write Metadata to DB|SQL-File
- convert files to WebP

```mermaid
flowchart LR;
  A[local storage] --> B[[files to photo-db]]
  B --> C[Database]
  B --> D["`**local storage**
  ./Webp/..`"]
```

## Inifile

_example Inifile_

see also: `<prog> -c` : create Inifile

```Ini
[DB_dev]
enabled=true                      # <true> | <false>
rdbms=file                        # <pg> | <sqlite> | <file>
dbname=                           # empty if file
dbfile=                           # empty if file
hostname=                         # empty if file
password=                         # empty if file
port=                             # empty if file
username=                         # empty if file
sql_file=./qt_files_photo.sql     # <path/to/file.sql>

[DB_int]
enabled=true                      # <true> | <false>
rdbms=sqlite                      # <pg> | <sqlite> | <file>
dbname=                           # empty if sqlite
dbfile=./photo_gallery.sqlite     # <path/to/sqlite.db>
hostname=                         # empty if sqlite
password=                         # empty if sqlite
port=                             # empty if sqlite
username=                         # empty if sqlite
sql_to_file=                      # empty if sqlite

[DB_prod]
enabled=true                      # <true> | <false>
rdbms=pg                          # <pg> | <sqlite> | <file>
dbname=photo_gallery              # <my database>
dbfile=                           # empty if pg
hostname=rdbms_srv                # <database server> // IP-Address or FQDN
password=Top_Secret!              # <database user password>
port=8154                         # <database server port>
username=photo_rw_user            # <database user>
sql_to_file=                      # empty if pg


[APP_dev]
Logifle=./qt_files_photo.log      # <path/to/logfile.log>

[APP_int]
Logifle=./qt_files_photo.log      # <path/to/logfile.log>

[APP_prod]
Logifle=./qt_files_photo.log      # <path/to/logfile.log>
```

## DevOps

```mermaid
pie title me
         "ideas" : 90
         "time for realizations" : 7
         "money for realizations" : 3
```

### Software Bill of Materials (SBoM)

```Bash
nvm use --lts

atom -J-Xmx16g usages -o app.atom --slice-outfile ./dist/atom_usages_v0.1.0.json -l cpp ./src

cdxgen -o ./dist/sbom_v0.1.0.json -t cpp --usages-slices-file ./dist/atom_usages_v0.1.0.json --author "ZHENG Robert" --deep -r ./src
```

<p align="right">(<a href="#top">back to top</a>)</p>

## Github Page

[![GH-Page](https://img.shields.io/badge/Github-Pages-black?logo=github)](https://www.github.com/Zheng-Bote)

## Github Wiki

[![GH-Wiki](https://img.shields.io/badge/Github-Wiki-black?logo=github)](https://www.github.com/Zheng-Bote)

## Comments

> \[!NOTE]
> Useful information that users should know, even when skimming content.

> \[!TIP]
> Helpful advice for doing things better or more easily.

> \[!IMPORTANT]
> Key information users need to know to achieve their goal.

> \[!WARNING]
> Urgent info that needs immediate user attention to avoid problems.

> \[!CAUTION]
> Advises about risks or negative outcomes of certain actions.

<p align="right">(<a href="#top">back to top</a>)</p>

## Screenshots

![App Screenshot](https://via.placeholder.com/468x300?text=App+Screenshot+Here)

<p align="right">(<a href="#top">back to top</a>)</p>

# Authors and License

## License

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://choosealicense.com/licenses/mit/)

Copyright (c) 2024 ZHENG Robert

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

        https://choosealicense.com/licenses/mit/

## Authors

- [![Zheng Robert](https://img.shields.io/badge/Github-Zheng_Robert-black?logo=github)](https://www.github.com/Zheng-Bote)

### Code Contributors

![Contributors](https://img.shields.io/github/contributors/Zheng-Bote/qt_files_photo-gallery?color=dark-green)

[![Zheng Robert](https://img.shields.io/badge/Github-Zheng_Robert-black?logo=github)](https://www.github.com/Zheng-Bote)

<hr>

:vulcan_salute:

<p align="right">(<a href="#top">back to top</a>)</p>
