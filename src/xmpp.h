/*
 * =====================================================================================
 *
 *       Filename:  xmpp.h
 *
 *    Description:  xmpp session manager
 *
 *        Version:  1.0
 *        Created:  04/02/2014 09:59:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Simone Vellei (sve), henomis@gmail.com
 *
 * =====================================================================================
 */

#ifndef _XMPP_H_
#define _XMPP_H_

#include <strophe.h>
#include "handlers.h"

int do_xmpp(char *jid, char *pass);

#endif
