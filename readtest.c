//
//  readtest.c
//  fork_test
//
//  Created by 陈诗妮 on 12-10-10.
//  
//

#include <unistd.h>
#include <sys/types.h>
#include <error.h>
main()
{
    int pipe_fd[2];//管道创建 #include<unistd.h>  int pipe(int fd[2]);
    pid_t pid;
    char r_buf[100];
    char w_buf[4];
    char* p_wbuf;
    int r_num;
    int cmd;
    
    memset(r_buf,0,sizeof(r_buf));
    memset(w_buf,0,sizeof(w_buf));
    p_wbuf=w_buf;
    if(pipe(pipe_fd)<0)
    {
        printf("pipe create error\n");
        return -1;
    }
    else if((pid=fork())==0)
    {
        printf("\n");
        close(pipe_fd[1]);
        sleep(3);//确保父进程关闭写端
        r_num=read(pipe_fd[0],r_buf,100);//返回min(请求数据量,管道数据量)
        printf("read num id %d,the data read from the pipe is %d\n,",r_num,atoi(r_buf));
        
        close(pipe_fd[0]);
        exit(1);
    }
    else if(pid>0)
    {
        close(pipe_fd[0]);
        strcpy(w_buf,"456");
        if(write(pipe_fd[1],w_buf,4)!=-1)//如果顺利write()则返回实际写入字节数，否则返回-1，错误代码写入errno
            printf("parent write over\n");
        close(pipe_fd[1]);
        printf("parent close fd[1] over\n");
        sleep(10);
    }
}


/*
 程序输出结果
 parent write over
 parent close fd[1] over
 
 read num id 4,the data read from the pipe is 456

 */
