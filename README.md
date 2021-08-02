# PAM password logger

[![Debian 10 - tested](https://img.shields.io/badge/Debian%2010-tested-green.svg)](https://shields.io/)
[![Ubuntu 2020.4 - tested](https://img.shields.io/badge/Ubuntu%202020.4-tested-green.svg)](https://shields.io/)
[![CentOS 8.4 - tested](https://img.shields.io/badge/CentOS%208.4-tested-green.svg)](https://shields.io/)

## What's this?

A minimalistic pluggable authentication modules (PAM) module that hooks into the linux authentication process to write the username, password and source host into a logfile. To learn more about what PAM is and how it works see [1]. The code is a modified version of this project [2]. Slight modifications for the use with other OS (versions) may be necessary.

## How to use it

> The instructions are for Debian / Ubuntu. This also works on CentOS but requires some modifications, see my answer [HERE](https://github.com/Cr4ckC4t/pam-pwlogger/issues/1).

1. In order to build the module the `libpam-dev` library is required.
```
# apt search libpam
  [...]
  libpam0g-dev/stable,now 1.3.1-5 amd64
    Development files for PAM
  [...]
  
# apt install libpam0g-dev
```
2. After installing the necessary dev files run `make`.
```
# make
  cc  -Wall -Wpedantic -c pam_pwlog.c -o pam_pwlog.o
  ld --shared -o pam_pwlog.so pam_pwlog.o -lpam -lpam_misc
```
3. Subsequently, update the file permissions to `0644` and store the module in a place where PAM can find it, i.e. `/lib/security/` or `/lib/*/security/`.
```
# chmod 0644 pam_pwlog.so && mv pam_pwlog.so /lib/security/
```
4. Finally update the PAM configuration in `/etc/pam.d/common-auth` to monitor all authentications. Alternatively, only update the configuration file for the specific service that you intend to monitor (e.g. `/etc/pam.d/sshd` for `ssh`). Add the following line to enable the module. (Again, see [1] for details.)

```
auth    optional                        pam_pwlog.so
```

## Disclaimer

Tinkering with PAM can easily break your entire authentication. Use at your own risk.

## Resources
[1] https://doc.opensuse.org/documentation/leap/archive/42.2/security/html/book.security/cha.pam.html

[2] http://www.adeptus-mechanicus.com/codex/logsshp/logsshp.html
