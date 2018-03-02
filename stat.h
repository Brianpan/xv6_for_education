#define T_DIR  1   // Directory
#define T_FILE 2   // File
#define T_DEV  3   // Device

struct stat {
  short type;  // Type of file
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short nlink; // Number of links to file
  uint size;   // Size of file in bytes
};

// define user process stat
enum uprocstate { UUNUSED, UEMBRYO, USLEEPING, URUNNABLE, URUNNING, UZOMBIE };

struct uproc {
  char name[16];
  int pid;
  int ppid;
  uint sz;                     // Size of process memory (bytes)
  enum uprocstate state;        // Process state
  int killed;				   // If non-zero, have been killed
  int waiting;                 // If non-zero, sleeping on chan
};