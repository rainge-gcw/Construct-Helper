//
// Created by hadoop on 1/20/23.
//

#ifndef CLION_JUDGEOPERATION_H
#define CLION_JUDGEOPERATION_H
#include<bits/stdc++.h>
#include <stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/resource.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include <sys/types.h>
#include <sys/file.h>
#include <cstdio>
#include <cstring>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sched.h>
#include <pthread.h>
#include <unistd.h>
#include <grp.h>
#include <dlfcn.h>
#include <cerrno>
#include <sched.h>
#include <seccomp.h>
#include "poolOperation.h"

#define UNLIMITED (-1)
#define LOG_ERROR(error_code) LOG_FATAL(log_fp, "Error: "#error_code);
#define ERROR_EXIT(error_code)\
    {\
        LOG_ERROR(error_code);  \
        _result->error = error_code; \
        log_close(log_fp);  \
        return; \
    }
#define ARGS_MAX_NUMBER 256
#define ENV_MAX_NUMBER 256
#define log_buffer_size 8192
#define LOG_LEVEL_FATAL 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DEBUG 3
#define LOG_FATAL(log_fp, x...)   log_write(LOG_LEVEL_FATAL, __FILE__, __LINE__, log_fp, ##x)
#define CHILD_ERROR_EXIT(error_code)\
    {\
        LOG_FATAL(log_fp, "Error: System errno: %s; Internal errno: "#error_code, strerror(errno)); \
        close_file(input_file); \
        if (output_file == error_file) { \
            close_file(output_file); \
        } else { \
            close_file(output_file); \
            close_file(error_file);  \
        } \
        raise(SIGUSR1);  \
        exit(EXIT_FAILURE); \
    }
enum {
    SUCCESS = 0,
    INVALID_CONFIG = -1,
    FORK_FAILED = -2,
    PTHREAD_FAILED = -3,
    WAIT_FAILED = -4,
    ROOT_REQUIRED = -5,
    LOAD_SECCOMP_FAILED = -6,
    SETRLIMIT_FAILED = -7,
    DUP2_FAILED = -8,
    SETUID_FAILED = -9,
    EXECVE_FAILED = -10,
    SPJ_ERROR = -11,
    COMPLIE_ERROR=-12
};
struct config {
    int max_cpu_time;
    int max_real_time;
    long max_memory;
    long max_stack;
    int max_process_number;
    long max_output_size;
    int memory_limit_check_only;
    string exe_path;
    string input_path;
    string output_path;
    string error_path;
    char *args[ARGS_MAX_NUMBER];
    char *env[ENV_MAX_NUMBER];
    string log_path;
    string seccomp_rule_name;
    uid_t uid;
    gid_t gid;
};
enum {
    WRONG_ANSWER = -1,
    CPU_TIME_LIMIT_EXCEEDED = 1,
    REAL_TIME_LIMIT_EXCEEDED = 2,
    MEMORY_LIMIT_EXCEEDED = 3,
    RUNTIME_ERROR = 4,
    SYSTEM_ERROR = 5
};


struct result {
    int cpu_time;
    int real_time;
    long memory;
    int signal;
    int exit_code;
    int error;
    int result;
};

struct timeout_killer_args {
    int pid;
    int timeout;
};

struct info{
    result res;
    string information;
};

class JudgeOperator{
public:
    static void construct_input(){

    }
    static void construct_output(){

    }
    static info stand_judge(const string &code,const string &stand_input,const string& stand_output){

        //获取池
        string url;
        int id=judge_poolOperator.get_pool(url);//../judge_pool/id
        struct result *r;
        r=(struct result *)malloc(sizeof(struct result));
        struct config *c;
        c=(struct config *)malloc(sizeof(struct config));
        c->max_cpu_time=5000;
        c->max_real_time=-1;
        c->max_memory=104857600;
        c->max_stack=104857600;
        c->max_process_number=1;
        c->max_output_size=int(1e7);
        c->memory_limit_check_only=0;


        FileOperator::write_txt(url+"/code.cpp",code);
        string order="gcc "+url+"/code.cpp -ldl -lseccomp -o "+url+"/code >"+url+"/log.txt -fmax-errors=100";
        if(system(order.c_str())==-1){//编译失败
            init_result(r);
            r->error=COMPLIE_ERROR;
            r->result=COMPLIE_ERROR;
            string ce_info;
            FileOperator::read_txt(url+"/log.txt",ce_info);
            return {*r,ce_info};
        }
        c->exe_path=(url+"/code");
        c->input_path=stand_input;
        c->output_path=(url+"/data.out");
        c->error_path=(url+"/err.txt");
        c->log_path=(url+"/log.txt");
        c->seccomp_rule_name="c_cpp";
        c->uid=0;
        c->gid=0;
        run(c,r);
        //释放池

        string res_info="AC";
        if(FileOperator::read_txt_without_end_of_line(url+"/data.out")!=FileOperator::read_txt_without_end_of_line(stand_output)){//WA
            res_info="WA\n";
            FileOperator::read_txt_limit(url+"/data.out",res_info,300);
        }else if(r->result==1||r->result==2){
            res_info="TLE";
        }else if(r->result==3){
            res_info="MLE";
        }else if(r->result==4){
            res_info="RE";
        }else if(r->result==5){
            res_info="System error";
        }
        judge_poolOperator.free_pool(id);
        return {*r,res_info};
    }
    static void test(int max_time,long max_memory,char * exe_path,char *input_path,char* output_path,
                     char* error_path,char* log_path
    ){
        struct config *c;
        c=(struct config *)malloc(sizeof(struct config));
        c->max_cpu_time=max_time;
        c->max_real_time=max_time;
        c->max_memory=max_memory;
        c->max_stack=104857600;
        c->max_process_number=1;
        c->max_output_size=int(1e7);
        c->memory_limit_check_only=0;
        c->exe_path=exe_path;
        c->input_path=input_path;
        c->output_path=output_path;
        c->error_path=error_path;
        c->log_path=log_path;
        c->seccomp_rule_name="c_cpp";
        c->uid=0;
        c->gid=0;
        struct result *r;
        r=(struct result *)malloc(sizeof(struct result));
        run(c,r);
        cout<<"====="<<endl;
        cout<<r->cpu_time<<endl;
        cout<<r->real_time<<endl;
        cout<<r->memory<<endl;
        cout<<r->signal<<endl;
        cout<<r->exit_code<<endl;
        cout<<r->result<<endl;
        cout<<r->error<<endl;
    }

    //run
    static void run(struct config *, struct result *);
    static void init_result(struct result *_result);

    //log
    static FILE *log_open(const char *filename);
    static void log_close(FILE *log_fp);
    static void log_write(int level, const char *source_filename, const int line, const FILE *log_fp, const char *fmt, ...);

    //child
    static void child_process(FILE *log_fp, struct config *_config);
    static void close_file(FILE *fp);

    //
    static int c_cpp_seccomp_rules(struct config *_config, bool allow_write_file);

    static void *timeout_killer(void *timeout_killer_args);
    static int kill_pid(pid_t pid);

};

void JudgeOperator::init_result(struct result *_result) {
    _result->result = _result->error = SUCCESS;
    _result->cpu_time = _result->real_time = _result->signal = _result->exit_code = 0;
    _result->memory = 0;
}

void JudgeOperator::run(struct config *_config, struct result *_result) {
    FILE *log_fp = log_open(_config->log_path.c_str());
    // init result
    init_result(_result);

    // check whether current user is root
    uid_t uid = getuid();
    if (uid != 0) {
        ERROR_EXIT(ROOT_REQUIRED);
    }
    // check args
    if ((_config->max_cpu_time < 1 && _config->max_cpu_time != UNLIMITED) ||
        (_config->max_real_time < 1 && _config->max_real_time != UNLIMITED) ||
        (_config->max_stack < 1) ||
        (_config->max_memory < 1 && _config->max_memory != UNLIMITED) ||
        (_config->max_process_number < 1 && _config->max_process_number != UNLIMITED) ||
        (_config->max_output_size < 1 && _config->max_output_size != UNLIMITED)) {
        ERROR_EXIT(INVALID_CONFIG);
    }

    if ((_config->max_cpu_time < 1 && _config->max_cpu_time != UNLIMITED) ||
        (_config->max_real_time < 1 && _config->max_real_time != UNLIMITED) ||
        (_config->max_stack < 1) ||
        (_config->max_memory < 1 && _config->max_memory != UNLIMITED) ||
        (_config->max_process_number < 1 && _config->max_process_number != UNLIMITED) ||
        (_config->max_output_size < 1 && _config->max_output_size != UNLIMITED)) {
        ERROR_EXIT(INVALID_CONFIG);
    }
    struct timeval start{}, end{};
    gettimeofday(&start, nullptr);
    pid_t child_pid = fork();

    if (child_pid < 0) {
        ERROR_EXIT(FORK_FAILED);
    }
    else if (child_pid == 0) {
        child_process(log_fp, _config);
    }
    else if (child_pid > 0) {
        // create new thread to monitor process running time
        pthread_t tid = 0;
        if (_config->max_real_time != UNLIMITED) {
            struct timeout_killer_args killer_args{};

            killer_args.timeout = _config->max_real_time;
            killer_args.pid = child_pid;
            if (pthread_create(&tid, nullptr, timeout_killer, (void *) (&killer_args)) != 0) {
                kill_pid(child_pid);
                ERROR_EXIT(PTHREAD_FAILED);
            }
        }

        int status;
        struct rusage resource_usage{};

        // wait for child process to terminate
        // on success, returns the process ID of the child whose state has changed;
        // On error, -1 is returned.
        if (wait4(child_pid, &status, WSTOPPED, &resource_usage) == -1) {
            kill_pid(child_pid);
            ERROR_EXIT(WAIT_FAILED);
        }
        // get end time
        gettimeofday(&end, nullptr);
        _result->real_time = (int) (end.tv_sec * 1000 + end.tv_usec / 1000 - start.tv_sec * 1000 -
                                    start.tv_usec / 1000);

        // process exited, we may need to cancel timeout killer thread
        if (_config->max_real_time != UNLIMITED) {
            if (pthread_cancel(tid) != 0) {
                // todo logging
            };
        }

        if (WIFSIGNALED(status) != 0) {
            _result->signal = WTERMSIG(status);
        }

        if (_result->signal == SIGUSR1) {
            _result->result = SYSTEM_ERROR;
        } else {
            _result->exit_code = WEXITSTATUS(status);
            _result->cpu_time = (int) (resource_usage.ru_utime.tv_sec * 1000 +
                                       resource_usage.ru_utime.tv_usec / 1000);
            _result->memory = resource_usage.ru_maxrss * 1024;

            if (_result->exit_code != 0) {
                _result->result = RUNTIME_ERROR;
            }

            if (_result->signal == SIGSEGV) {
                if (_config->max_memory != UNLIMITED && _result->memory > _config->max_memory) {
                    _result->result = MEMORY_LIMIT_EXCEEDED;
                } else {
                    _result->result = RUNTIME_ERROR;
                }
            } else {
                if (_result->signal != 0) {
                    _result->result = RUNTIME_ERROR;
                }
                if (_config->max_memory != UNLIMITED && _result->memory > _config->max_memory) {
                    _result->result = MEMORY_LIMIT_EXCEEDED;
                }
                if (_config->max_real_time != UNLIMITED && _result->real_time > _config->max_real_time) {
                    _result->result = REAL_TIME_LIMIT_EXCEEDED;
                }
                if (_config->max_cpu_time != UNLIMITED && _result->cpu_time > _config->max_cpu_time) {
                    _result->result = CPU_TIME_LIMIT_EXCEEDED;
                }
            }
        }

        log_close(log_fp);
    }


}

//log
FILE *JudgeOperator::log_open(const char *filename) {
    FILE *log_fp = fopen(filename, "a");
    if (log_fp == nullptr) {
        fprintf(stderr, "can not open log file %s", filename);
    }
    return log_fp;
}

void JudgeOperator::log_close(FILE *log_fp) {
    if (log_fp != nullptr) {
        fclose(log_fp);
    }
}

void
JudgeOperator::log_write(int level, const char *source_filename, const int line, const FILE *log_fp, const char *fmt,
                         ...) {
    char LOG_LEVEL_NOTE[][10] = {"FATAL", "WARNING", "INFO", "DEBUG"};
    if (log_fp == nullptr) {
        fprintf(stderr, "can not open log file");
        return;
    }
    static char buffer[log_buffer_size];
    static char log_buffer[log_buffer_size];
    static char datetime[100];
    static char line_str[20];
    static time_t now;
    now = time(nullptr);

    strftime(datetime, 99, "%Y-%m-%d %H:%M:%S", localtime(&now));
    snprintf(line_str, 19, "%d", line);
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(log_buffer, log_buffer_size, fmt, ap);
    va_end(ap);

    int count = snprintf(buffer, log_buffer_size,
                         "%s [%s] [%s:%s]%s\n",
                         LOG_LEVEL_NOTE[level], datetime, source_filename, line_str, log_buffer);
    // fprintf(stderr, "%s", buffer);
    int log_fd = fileno((FILE *) log_fp);
    if (flock(log_fd, LOCK_EX) == 0) {
        if (write(log_fd, buffer, (size_t) count) < 0) {
            fprintf(stderr, "write error");
            return;
        }
        flock(log_fd, LOCK_UN);
    }
    else {
        fprintf(stderr, "flock error");
        return;
    }

}

void JudgeOperator::child_process(FILE *log_fp, struct config *_config) {
    FILE *input_file = nullptr, *output_file = nullptr, *error_file = nullptr;
    if (_config->max_stack != UNLIMITED) {
        struct rlimit max_stack{};
        max_stack.rlim_cur = max_stack.rlim_max = (rlim_t) (_config->max_stack);
        if (setrlimit(RLIMIT_STACK, &max_stack) != 0) {
            CHILD_ERROR_EXIT(SETRLIMIT_FAILED);
        }
    }
    // set memory limit
    // if memory_limit_check_only == 0, we only check memory usage number, because setrlimit(maxrss) will cause some crash issues
    if (_config->memory_limit_check_only == 0) {
        if (_config->max_memory != UNLIMITED) {
            struct rlimit max_memory{};
            max_memory.rlim_cur = max_memory.rlim_max = (rlim_t) (_config->max_memory) * 2;
            if (setrlimit(RLIMIT_AS, &max_memory) != 0) {
                CHILD_ERROR_EXIT(SETRLIMIT_FAILED);
            }
        }
    }
    if (_config->max_cpu_time != UNLIMITED) {
        struct rlimit max_cpu_time{};
        max_cpu_time.rlim_cur = max_cpu_time.rlim_max = (rlim_t) ((_config->max_cpu_time + 1000) / 1000);
        if (setrlimit(RLIMIT_CPU, &max_cpu_time) != 0) {
            CHILD_ERROR_EXIT(SETRLIMIT_FAILED);
        }
    }
    // set max process number limit
    if (_config->max_process_number != UNLIMITED) {
        struct rlimit max_process_number{};
        max_process_number.rlim_cur = max_process_number.rlim_max = (rlim_t) _config->max_process_number;
        if (setrlimit(RLIMIT_NPROC, &max_process_number) != 0) {
            CHILD_ERROR_EXIT(SETRLIMIT_FAILED);
        }
    }
    // set max output size limit
    if (_config->max_output_size != UNLIMITED) {
        struct rlimit max_output_size{};
        max_output_size.rlim_cur = max_output_size.rlim_max = (rlim_t ) _config->max_output_size;
        if (setrlimit(RLIMIT_FSIZE, &max_output_size) != 0) {
            CHILD_ERROR_EXIT(SETRLIMIT_FAILED);
        }
    }
    if (_config->input_path .size()>0) {
        input_file = fopen(_config->input_path.c_str(), "r");
        if (input_file == nullptr) {
            CHILD_ERROR_EXIT(DUP2_FAILED);
        }
        // redirect file -> stdin
        // On success, these system calls return the new descriptor.
        // On error, -1 is returned, and errno is set appropriately.
        if (dup2(fileno(input_file), fileno(stdin)) == -1) {
            // todo log
            CHILD_ERROR_EXIT(DUP2_FAILED);
        }
    }
    if (_config->output_path .size()>0) {
        output_file = fopen(_config->output_path.c_str(), "w");
        if (output_file == nullptr) {
            CHILD_ERROR_EXIT(DUP2_FAILED);
        }
        // redirect stdout -> file
        if (dup2(fileno(output_file), fileno(stdout)) == -1) {
            CHILD_ERROR_EXIT(DUP2_FAILED);
        }
    }
    if (_config->error_path .size()>0) {
        fprintf(stderr, "%s\n",_config->error_path.c_str());
        // if outfile and error_file is the same path, we use the same file pointer
        if (_config->output_path.size()>0  && _config->output_path==_config->error_path) {
            error_file = output_file;
        }
        else {
            error_file = fopen(_config->error_path.c_str(), "w");
            if (error_file == nullptr) {
                // todo log
                CHILD_ERROR_EXIT(DUP2_FAILED);
            }
        }
        // redirect stderr -> file
        fprintf(stderr, "%s\n",_config->error_path.c_str());
        if (dup2(fileno(error_file), fileno(stderr)) == -1) {
            // todo log
            CHILD_ERROR_EXIT(DUP2_FAILED);
        }
    }
    gid_t group_list[] = {_config->gid};
    if (_config->gid != -1 && (setgid(_config->gid) == -1 || setgroups(sizeof(group_list) / sizeof(gid_t), group_list) == -1)) {
        CHILD_ERROR_EXIT(SETUID_FAILED);
    }
    if (_config->uid != -1 && setuid(_config->uid) == -1) {
        CHILD_ERROR_EXIT(SETUID_FAILED);
    }
    if (_config->seccomp_rule_name.size()) {
        if ("c_cpp"==_config->seccomp_rule_name) {
            if (c_cpp_seccomp_rules(_config,true) != SUCCESS) {
                CHILD_ERROR_EXIT(LOAD_SECCOMP_FAILED);
            }
        }
        else {
            // rule does not exist
            CHILD_ERROR_EXIT(LOAD_SECCOMP_FAILED);
        }
    }
    execve(_config->exe_path.c_str(), _config->args, _config->env);
    CHILD_ERROR_EXIT(EXECVE_FAILED);

}

void JudgeOperator::close_file(FILE *fp) {
    if (fp != nullptr) {
        fclose(fp);
    }
}

int JudgeOperator::c_cpp_seccomp_rules(struct config *_config, bool allow_write_file) {
    int syscalls_whitelist[] = {SCMP_SYS(read), SCMP_SYS(fstat),
                                SCMP_SYS(mmap), SCMP_SYS(mprotect),
                                SCMP_SYS(munmap), SCMP_SYS(uname),
                                SCMP_SYS(arch_prctl), SCMP_SYS(brk),
                                SCMP_SYS(access), SCMP_SYS(exit_group),
                                SCMP_SYS(close), SCMP_SYS(readlink),
                                SCMP_SYS(sysinfo), SCMP_SYS(write),
                                SCMP_SYS(writev), SCMP_SYS(lseek),
                                SCMP_SYS(clock_gettime), SCMP_SYS(pread64),
                                SCMP_SYS(newfstatat),SCMP_SYS(lseek),
                                SCMP_SYS(rseq),SCMP_SYS(getrandom),
                                SCMP_SYS(prlimit64),SCMP_SYS(set_robust_list),
                                SCMP_SYS(openat),SCMP_SYS(set_tid_address)

    }; // add extra rule for pread64
    //fprintf(stderr, "123");
    int syscalls_whitelist_length = sizeof(syscalls_whitelist) / sizeof(int);
    scmp_filter_ctx ctx = nullptr;
    // load seccomp rules
    ctx = seccomp_init(SCMP_ACT_KILL);
    //fprintf(stderr, "123");

    if (!ctx) {
        return LOAD_SECCOMP_FAILED;
    }
    //fprintf(stderr, "123");

    for (int i = 0; i < syscalls_whitelist_length; i++) {
        if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, syscalls_whitelist[i], 0) != 0) {
            return LOAD_SECCOMP_FAILED;
        }
    }
    // add extra rule for execve
    if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(execve), 1, SCMP_A0(SCMP_CMP_EQ, (scmp_datum_t)(_config->exe_path.c_str()))) != 0) {
        return LOAD_SECCOMP_FAILED;
    }
    if (!allow_write_file) {
        // do not allow "w" and "rw"
        if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 1, SCMP_CMP(1, SCMP_CMP_MASKED_EQ, O_WRONLY | O_RDWR, 0)) != 0) {
            return LOAD_SECCOMP_FAILED;
        }
        if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(openat), 1, SCMP_CMP(2, SCMP_CMP_MASKED_EQ, O_WRONLY | O_RDWR, 0)) != 0) {
            return LOAD_SECCOMP_FAILED;
        }
    } else {
        if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 0) != 0) {
            return LOAD_SECCOMP_FAILED;
        }
        if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(dup), 0) != 0) {
            return LOAD_SECCOMP_FAILED;
        }
        if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(dup2), 0) != 0) {
            return LOAD_SECCOMP_FAILED;
        }
        if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(dup3), 0) != 0) {
            return LOAD_SECCOMP_FAILED;
        }
    }

    //fprintf(stderr, "123");
    if (seccomp_load(ctx) != 0) {
        return LOAD_SECCOMP_FAILED;
    }
    seccomp_release(ctx);
    //fprintf(stderr, "123");
    return SUCCESS;
}

void *JudgeOperator::timeout_killer(void *timeout_killer_args) {
    // this is a new thread, kill the process if timeout
    pid_t pid = ((struct timeout_killer_args *)timeout_killer_args)->pid;
    int timeout = ((struct timeout_killer_args *)timeout_killer_args)->timeout;
    // On success, pthread_detach() returns 0; on error, it returns an error number.
    if (pthread_detach(pthread_self()) != 0) {
        kill_pid(pid);
        return nullptr;
    }
    // usleep can't be used, for time args must < 1000ms
    // this may sleep longer that expected, but we will have a check at the end
    if (sleep((unsigned int)((timeout + 1000) / 1000)) != 0) {
        kill_pid(pid);
        return nullptr;
    }
    if (kill_pid(pid) != 0) {
        return nullptr;
    }
    return nullptr;
}

int JudgeOperator::kill_pid(pid_t pid) {
    return kill(pid, SIGKILL);
}


#endif //CLION_JUDGEOPERATION_H
