/* vim:set cin ft=c sw=4 sts=4 ts=8 et ai cino=Ls\:0t0(0 : -*- mode:c;fill-column:80;tab-width:8;c-basic-offset:4;indent-tabs-mode:nil;c-file-style:"k&r" -*-*/
/* NetHack may be freely redistributed.  See license for details. */

#ifndef NETHACK_CLIENT_H
# define NETHACK_CLIENT_H

# include "nethack_types.h"

# ifdef NETHACK_CLIENT_H_IN_LIBNETHACK_CLIENT
#  define EXPORT(x) AIMAKE_EXPORT(x)
# else
#  define EXPORT(x) AIMAKE_IMPORT(x)
# endif

/* extra return status for nhnet_command and nhnet_restore_game */
# define ERR_NETWORK_ERROR (20000)

enum authresult {
    NO_CONNECTION,
    AUTH_FAILED_UNKNOWN_USER,
    AUTH_FAILED_BAD_PASSWORD,
    AUTH_SUCCESS_NEW,
    AUTH_SUCCESS_RECONNECT
};


struct nhnet_game {
    int gameid;
    enum nh_log_status status;
    struct nh_game_info i;
};


struct nhnet_server_version {
    int major, minor, patchlevel;
};

extern struct nhnet_server_version EXPORT(nhnet_server_ver);


extern int EXPORT(nhnet_connect) (
    const char *host, int port, const char *user,
    const char *pass, const char *email, int reg_user);
extern void EXPORT(nhnet_disconnect) (void);
extern int EXPORT(nhnet_connected) (void);
extern int EXPORT(nhnet_active) (void);
extern nhnet_game_p EXPORT(nhnet_list_games) (
    int done, int show_all, int *count);

extern void EXPORT(nhnet_lib_init) (const struct nh_window_procs *);
extern void EXPORT(nhnet_lib_exit) (void);
extern nh_bool EXPORT(nhnet_exit_game) (int exit_type);
extern int EXPORT(nhnet_restore_game) (int gid,
                                     struct nh_window_procs *rwinprocs);
extern nh_bool EXPORT(nhnet_start_game) (const char *name, int role, int race,
                                       int gend, int align,
                                       enum nh_game_modes playmode);
extern int EXPORT(nhnet_command) (const char *cmd, int rep,
                                struct nh_cmd_arg *arg);
/* no nhnet_get_copyright_banner; the client should display its own copyright */
extern nh_bool EXPORT(nhnet_view_replay_start) (int fd,
                                              struct nh_window_procs *rwinprocs,
                                              struct nh_replay_info *info);
extern nh_bool EXPORT(nhnet_view_replay_step) (struct nh_replay_info *info,
                                             enum replay_control action,
                                             int count);
extern void EXPORT(nhnet_view_replay_finish) (void);
extern nh_cmd_desc_p EXPORT(nhnet_get_commands) (int *count);
extern nh_cmd_desc_p EXPORT(nhnet_get_object_commands) (
    int *count, char invlet);
extern nh_drawing_info_p EXPORT(nhnet_get_drawing_info) (void);
extern nh_bool EXPORT(nhnet_set_option) (const char *name,
                                       union nh_optvalue value, nh_bool isstr);
extern nh_option_desc_p EXPORT(nhnet_get_options) (
    enum nh_option_list list);
/* no nhnet_get_option_string; the client translates the values locally */
extern void EXPORT(nhnet_describe_pos) (
    int x, int y, struct nh_desc_buf *bufs, int *is_in);
extern nh_roles_info_p EXPORT(nhnet_get_roles) (void);
extern char_p EXPORT(nhnet_build_plselection_prompt) (
    char *, int, int, int, int, int);
extern const_char_p EXPORT(nhnet_root_plselection_prompt) (
    char *, int, int, int, int, int);
extern nh_topten_entry_p EXPORT(nhnet_get_topten) (
    int *out_len, char *statusbuf, const char *player, int top,
    int around, nh_bool own);
extern int EXPORT(nhnet_change_email) (const char *email);
extern int EXPORT(nhnet_change_password) (const char *password);

# undef EXPORT

# if defined(NHNET_TRANSPARENT) && \
    !defined(NETHACK_CLIENT_H_IN_LIBNETHACK_CLIENT)
#  define nh_command                  nhnet_command
#  define nh_exit_game                nhnet_exit_game
#  define nh_view_replay_start        nhnet_view_replay_start
#  define nh_view_replay_step         nhnet_view_replay_step
#  define nh_view_replay_finish       nhnet_view_replay_finish
#  define nh_get_commands             nhnet_get_commands
#  define nh_get_object_commands      nhnet_get_object_commands
#  define nh_get_drawing_info         nhnet_get_drawing_info
#  define nh_set_option               nhnet_set_option
#  define nh_get_options              nhnet_get_options
#  define nh_describe_pos             nhnet_describe_pos
#  define nh_get_roles                nhnet_get_roles
#  define nh_build_plselection_prompt nhnet_build_plselection_prompt
#  define nh_root_plselection_prompt  nhnet_root_plselection_prompt
#  define nh_get_topten               nhnet_get_topten
# endif

#endif
