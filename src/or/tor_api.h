/* Copyright (c) 2001 Matej Pfajfar.
 * Copyright (c) 2001-2004, Roger Dingledine.
 * Copyright (c) 2004-2006, Roger Dingledine, Nick Mathewson.
 * Copyright (c) 2007-2017, The Tor Project, Inc. */
/* See LICENSE for licensing information */

/**
 * \file tor_api.h
 * \brief Public C API for the Tor network service.
 *
 * This interface is intended for use by programs that need to link Tor as
 * a library, and launch it in a separate thread.  If you have the ability
 * to run Tor as a separate executable, you should probably do that instead
 * of embedding it as a library.
 **/

#ifndef TOR_API_H
#define TOR_API_H

typedef struct tor_main_configuration_t tor_main_configuration_t;

/**
 * Create and return a new tor_main_configuration().
 */
tor_main_configuration_t *tor_main_configuration_new(void);

/**
 * Set the command-line arguments in <b>cfg</b>.
 *
 * The <b>argc</b> and <b>argv</b> values here are as for main().  The
 * contents of the argv pointer must remain unchanged until tor_run_main() has
 * finished and you call tor_main_configuration_free().
 *
 * Return 0 on success, -1 on failure.
 */
int tor_main_configuration_set_command_line(tor_main_configuration_t *cfg,
                                            int argc, char *argv[]);
/**
 * Release all storage held in <b>cfg</b>.
 *
 * Once you have passed a tor_main_configuration_t to tor_run_main(), you
 * must not free it until tor_run_main() has finished.
 */
void tor_main_configuration_free(tor_main_configuration_t *cfg);

/**
 * Run the tor process, as if from the command line.
 *
 * The command line arguments from tor_main_configuration_set_command_line()
 * are taken as if they had been passed to main().
 *
 * This function will not return until Tor is done running.  It returns zero
 * on success, and nonzero on failure.
 *
 * BUG 23848: In many cases, tor_main will call exit() or abort() instead of
 * returning.  This is not the intended long-term behavior; we are trying to
 * fix it.
 *
 * BUG 23847: You can only call tor_main() once in a single process; if it
 * returns and you call it again, you may crash. This is not intended
 * long-term behavior; we are trying to fix it.
 *
 * LIMITATION: You cannot run more than one instance of Tor in the same
 * process at the same time. Concurrent calls will cause undefined behavior.
 * We do not currently have plans to change this.
 */
int tor_run_main(const tor_main_configuration_t *);

/**
 * Run the tor process, as if from the command line.
 *
 * @deprecated Using this function from outside Tor is deprecated; you should
 * use use tor_run_main() instead.
 *
 * BUGS: This function has all the same bugs as tor_run_main().
 *
 * LIMITATIONS: This function has all the limitations of tor_run_main().
 */
int tor_main(int argc, char **argv);

#endif /* !defined(TOR_API_H) */

