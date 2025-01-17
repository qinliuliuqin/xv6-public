/**
 * Test Fast File System 1
 *
 * Test heuristic 1 (placing new directories in one of the least-utilized block groups).
 */

#include "types.h"
#include "user.h"
#include "fs.h"

#define TESTDIR1 "_testdir1"
#define TESTDIR2 "_testdir2"
#define TESTDIR3 "_testdir3"

int
makeandopendir(char *name)
{
  printf(1, "Making new directory... ");
  if (mkdir(name) < 0) {
  	printf(2, "failed call to mkdir\n");
  	exit();
  }
  int fd;
  if((fd = open(name, 0)) < 0){
    printf(2, "failed call to open\n");
    exit();
  }
  return fd;
}

int
main(int argc, char *argv[])
{
  printf(1, "This tests the first heuristic of the Fast File System.\n");
  printf(1, "As each directory is created, its inode is allocated in the least-utilized\n"\
	"block group. To prove this point, this test creates 3 directories, which should\n"\
	"be allocated into different block groups. As each directory is created, this\n"\
	"test outputs the amount of allocated data blocks in the block group that its\n"\
	"inode is in. Each directory is deleted at the end of this test so that it can\n"\
	"be called again. To test this script further, use command \"ffs\" to check\n"\
	"the block groups before the script.\n\n");

  int fd;
  struct fbgstat fbg;
  struct bgstat bg;

  // dir 1
  fd = makeandopendir(TESTDIR1);
  fbgstat(fd, &fbg);
  bgstat(fbg.inodebgroup, &bg);
  printf(1, "allocated in block group %d\n", fbg.inodebgroup);
  printf(1, "Block group %d: allocated data blocks: %d\n", fbg.inodebgroup, bg.allocateddatablocks);

  // dir 2
  fd = makeandopendir(TESTDIR2);
  fbgstat(fd, &fbg);
  bgstat(fbg.inodebgroup, &bg);
  printf(1, "allocated in block group %d\n", fbg.inodebgroup);
  printf(1, "Block group %d: allocated data blocks: %d\n", fbg.inodebgroup, bg.allocateddatablocks);

  // dir 3
  fd = makeandopendir(TESTDIR3);
  fbgstat(fd, &fbg);
  bgstat(fbg.inodebgroup, &bg);
  printf(1, "allocated in block group %d\n", fbg.inodebgroup);
  printf(1, "Block group %d: allocated data blocks: %d\n", fbg.inodebgroup, bg.allocateddatablocks);

  // delete all created directories
  printf(1, "Cleaning up...\n");
  if (unlink(TESTDIR1) < 0 || unlink(TESTDIR2) < 0 || unlink(TESTDIR3) < 0) {
  	printf(2, "failed to delete. Please git reset --hard (buggy test)\n");
  	exit();
  }

  exit();
}
