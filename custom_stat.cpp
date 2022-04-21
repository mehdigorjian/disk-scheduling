// COMPILATION: gcc custom_stat.cpp -o custom_stat -lstdc++
//         RUN: ./custom_stat FILE.EXTENTION
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void custom_stat(char *filename){
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1){
        // Error handling
        fprintf(stderr, "stat: cannot stat '%s': %s\n", filename,strerror(errno));
        exit(EXIT_FAILURE);
    } else {
        printf("%10s %s\n", "File:", filename);
        printf("%10s %ld\n", "Size:", file_stat.st_size);
        printf("%10s %ld\n", "Blocks:", file_stat.st_blocks);
        printf("%10s %ld\n", "IO Block:", file_stat.st_blksize);
        printf("%10s ", "File Type:");
        // getting the various file types
            // is it a regular file
            if(S_ISREG(file_stat.st_mode)) printf("regular file\n");
            // is it a directory
            if(S_ISDIR(file_stat.st_mode)) printf("directory\n");
            // is it a character device
            if(S_ISCHR(file_stat.st_mode)) printf("character device\n");
            // is it a block device
            if(S_ISBLK(file_stat.st_mode)) printf("block device\n");
            // is it a FIFO (named pipe)
            if(S_ISFIFO(file_stat.st_mode)) printf("FIFO (named pipe)\n");
            // is it a symbolic link
            if(S_ISLNK(file_stat.st_mode)) printf("symbolic link\n");
            // is it a socket
            if(S_ISSOCK(file_stat.st_mode)) printf("socket\n");
        printf("%10s %lx\n", "Device:",file_stat.st_dev);
        printf("%10s %lu\n", "Inode:", file_stat.st_ino);
        printf("%10s %lu\n", "Links:", file_stat.st_nlink);
        printf("%10s %04o\n", "Access:", file_stat.st_mode&0777);
        // acquiring Username from UID
        struct passwd *pws;
        pws = getpwuid(file_stat.st_uid);
        printf("%10s (%5d/%s)\n", "Uid:", file_stat.st_uid , pws->pw_name);
        //acquiring Group Name from GID
        struct group *grp;
        grp = getgrgid(file_stat.st_gid);
        printf("%10s (%5d/%s)\n", "Gid:", file_stat.st_gid , grp->gr_name);
        // format times (using ctime from time.h)
        printf("%10s %s", "Access:", ctime(&file_stat.st_atime));
        printf("%10s %s", "Modify:", ctime(&file_stat.st_mtime));
        printf("%10s %s", "Change:", ctime(&file_stat.st_ctime));
    }
}

int main(int argc, char* argv[]){
    if (argc == 1){
        // in case no other argument is provided
        fprintf(stderr,"stat: missing operand\n");
    } else {
        // print information of each argument
        for(int i=1;i<argc;i++){
            custom_stat(argv[i]);
        }
    }
    return 0;
}
// Here is how the structure returned by stat looks:
//     struct stat {
//                 dev_t     st_dev;         /* ID of device containing file */
//                 ino_t     st_ino;         /* Inode number */
//                 mode_t    st_mode;        /* File type and mode */
//                 nlink_t   st_nlink;       /* Number of hard links */
//                 uid_t     st_uid;         /* User ID of owner */
//                 gid_t     st_gid;         /* Group ID of owner */
//                 dev_t     st_rdev;        /* Device ID (if special file) */
//                 off_t     st_size;        /* Total size, in bytes */
//                 blksize_t st_blksize;     /* Block size for filesystem I/O */
//                 blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */
//                 struct timespec st_atim;  /* Time of last access */
//                 struct timespec st_mtim;  /* Time of last modification */
//                 struct timespec st_ctim;  /* Time of last status change */
//                 
//                 #define st_atime st_atim.tv_sec      /* Backward compatibility */
//                 #define st_mtime st_mtim.tv_sec
//                 #define st_ctime st_ctim.tv_sec
//     };
// Reference
// https://nipunbatra.github.io/os2020/labs/#lab-3