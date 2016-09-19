
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_CYCLE_H_INCLUDED_
#define _NGX_CYCLE_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>


#ifndef NGX_CYCLE_POOL_SIZE
#define NGX_CYCLE_POOL_SIZE     NGX_DEFAULT_POOL_SIZE
#endif


#define NGX_DEBUG_POINTS_STOP   1
#define NGX_DEBUG_POINTS_ABORT  2


typedef struct ngx_shm_zone_s  ngx_shm_zone_t;

typedef ngx_int_t (*ngx_shm_zone_init_pt) (ngx_shm_zone_t *zone, void *data);

struct ngx_shm_zone_s {
    void                     *data;
    ngx_shm_t                 shm;
    ngx_shm_zone_init_pt      init;
    void                     *tag;
    ngx_uint_t                noreuse;  /* unsigned  noreuse:1; */
};


struct ngx_cycle_s {
    // 保存着所有模块存储配置项的结构体的指针，它首先是一个数组，每个数组成员又是一个指针，
    // 这个指针指向另一个存储着指针的数组，因此会看到 void****
    void                  ****conf_ctx;
    // 内存池
    ngx_pool_t               *pool;

    // 日志模块中提供了生成基本 ngx_log_t 日志对象的功能，
    // 这里的 log 实际上是在还没有执行 ngx_init_cycle 方法前,
    // 也就是还没有解析配置前，如果没有信息需要输出到日志，就会暂时使用 log 对象，它会输出到屏幕。
    // 在 ngx_init_cycle 方法执行后，将会根据 nginx.conf 配置文件中的配置项，构造出正确的日志文件，
    // 此时会对 log 重新赋值
    ngx_log_t                *log;

    // 由 nginx.conf 配置文件读取到日志文件路径后，将开始初始化 error_log 日志文件，
    // 由于 log 对象还在用于输出日志到屏幕，这时会用 new_log 对象暂时性地替代 log 日志，
    // 待初始化成功后，会用 new_log 的地址覆盖上面的 log 指针
    ngx_log_t                 new_log;

    ngx_uint_t                log_use_stderr;  /* unsigned  log_use_stderr:1; */

    // 对于 poll、rtsig 这样的事件模块，会以有效文件句柄数来预先建立这些 ngx_connection_t 结构体，
    // 以加速事件的收集、分发。这里 files 就会保存所有 ngx_connection_t 的指针组成的数组，
    // files_n 就是指针的总数，而文件句柄的值用来访问 files 数组成员。
    ngx_connection_t        **files;
    // 可用连接池，与 free_connection_n 配合使用
    ngx_connection_t         *free_connections;
    // 可用连接池中的连接总数
    ngx_uint_t                free_connection_n;

    ngx_module_t            **modules;
    ngx_uint_t                modules_n;
    ngx_uint_t                modules_used;    /* unsigned  modules_used:1; */

    // 双向链表容器，元素类型是 ngx_connection_t 结构体，表示可重复使用连接队列。
    ngx_queue_t               reusable_connections_queue;

    // 动态数组，每个数组元素存储着 ngx_listening_t 成员，表示监听端口及相关的参数。
    ngx_array_t               listening;
    // 动态数组容器，它保存着 nginx 所有要操作的目录。
    // 如果有目录不存在，由会试图创建，而创建目录失败将会导致 nginx 启动失败。
    // 例如，上传文件的临时目录也在 pathes 中，如果没有权限创建，则会导致 nginx 无法启动。
    ngx_array_t               paths;
    ngx_array_t               config_dump;
    // 单链表容器，元素类型是 ngx_open_file_t 结构体，它表示 nginx 已经打开的所有文件。
    // 事实上，nginx 框架不会向 open_files 链表中添加文件，而是由对此感兴趣的模块向其中添加文件路径名，
    // nginx 框架会在 ngx_init_cycle 方法中打开这些文件。
    ngx_list_t                open_files;
    // 单链表容器，元素的类型是 ngx_shm_zone_t 结构体，每个元素表示一块共享内存。
    ngx_list_t                shared_memory;

    // 当前进程中所有连接对象的总数，与下面的 connections 成员配合使用。
    ngx_uint_t                connection_n;
    // 与 files 成员配合使用，指出 files 数组里元素的总数。
    ngx_uint_t                files_n;

    // 指向当前进程中的所有连接对象，与 connection_n 配合使用。
    ngx_connection_t         *connections;

    // 指向当前进程中的所有读事件对象，connection_n 同时表示所有读事件的总数。
    ngx_event_t              *read_events;
    // 指向当前进程中的所有写事件对象，connection_n 同时表示所有写事件的总数。
    ngx_event_t              *write_events;

    // 旧的 ngx_cycle_t 对象用于引用上一个 ngx_cycle_t 对象中的成员。例如 ngx_init_cycle 方法，
    // 在启动初期，需要建立一个临时的 ngx_cycle_t 对象保存一些变量，再调用 ngx_init_cycle 方法时就
    // 可以把旧的 ngx_cycle_t 对象传进去，而这时 old_cycle 对象就会保存这个前期的 ngx_cycle_t 对象。
    ngx_cycle_t              *old_cycle;

    // 配置文件相对于安装目录的路径名称。
    ngx_str_t                 conf_file;
    // nginx 处理配置文件时需要特殊处理的在命令行携带的参数，一般是 -g 选项携带的参数。
    ngx_str_t                 conf_param;
    // nginx 配置文件所在目录的路径。
    ngx_str_t                 conf_prefix;
    // nginx 安装目录的路径。
    ngx_str_t                 prefix;
    // 用于进程间同步的文件锁名称。
    ngx_str_t                 lock_file;
    // 使用 gethostname 系统调用得到的主机名
    ngx_str_t                 hostname;
};


typedef struct {
    ngx_flag_t                daemon;
    ngx_flag_t                master;

    ngx_msec_t                timer_resolution;

    ngx_int_t                 worker_processes;
    ngx_int_t                 debug_points;

    ngx_int_t                 rlimit_nofile;
    off_t                     rlimit_core;

    int                       priority;

    ngx_uint_t                cpu_affinity_auto;
    ngx_uint_t                cpu_affinity_n;
    ngx_cpuset_t             *cpu_affinity;

    char                     *username;
    ngx_uid_t                 user;
    ngx_gid_t                 group;

    ngx_str_t                 working_directory;
    ngx_str_t                 lock_file;

    ngx_str_t                 pid;
    ngx_str_t                 oldpid;

    ngx_array_t               env;
    char                    **environment;
} ngx_core_conf_t;


#define ngx_is_init_cycle(cycle)  (cycle->conf_ctx == NULL)


ngx_cycle_t *ngx_init_cycle(ngx_cycle_t *old_cycle);
ngx_int_t ngx_create_pidfile(ngx_str_t *name, ngx_log_t *log);
void ngx_delete_pidfile(ngx_cycle_t *cycle);
ngx_int_t ngx_signal_process(ngx_cycle_t *cycle, char *sig);
void ngx_reopen_files(ngx_cycle_t *cycle, ngx_uid_t user);
char **ngx_set_environment(ngx_cycle_t *cycle, ngx_uint_t *last);
ngx_pid_t ngx_exec_new_binary(ngx_cycle_t *cycle, char *const *argv);
ngx_cpuset_t *ngx_get_cpu_affinity(ngx_uint_t n);
ngx_shm_zone_t *ngx_shared_memory_add(ngx_conf_t *cf, ngx_str_t *name,
    size_t size, void *tag);


extern volatile ngx_cycle_t  *ngx_cycle;
extern ngx_array_t            ngx_old_cycles;
extern ngx_module_t           ngx_core_module;
extern ngx_uint_t             ngx_test_config;
extern ngx_uint_t             ngx_dump_config;
extern ngx_uint_t             ngx_quiet_mode;


#endif /* _NGX_CYCLE_H_INCLUDED_ */
