#pragma once

#include "../kernel/int.h"

#define ATA_BASE_PORT 0x1F0

#define ATA_DATA_REGISTER_OFFSET 0
#define ATA_ERROR_REGISTER_OFFSET 1
#define ATA_FEATURE_REGISTER_OFFSET 1
#define ATA_SECTOR_COUNT_REGISTER_OFFSET 2
//#define ATA_SECTOR_NUMBER_REGISTER_OFFSET 3
//#define ATA_CYLINDER_LOW_REGISTER_OFFSET 4
//#define ATA_CYLINDER_HIGH_REGISTER_OFFSET 5
#define ATA_LBA_LOW_REGISTER_OFFSET 3
#define ATA_LBA_MID_REGISTER_OFFSET 4
#define ATA_LBA_HIGH_REGISTER_OFFSET 5
#define ATA_DRIVE_HEAD_REGISTER_OFFSET 6
#define ATA_STATUS_REGISTER_OFFSET 7
#define ATA_COMMAND_REGISTER_OFFSET 7

#define ATA_ALTERNATE_STATUS_REGISTER_OFFSET 0
#define ATA_DEVICE_CONTROL_REGISTER_OFFSET 0
#define ATA_DEVICE_ADDRESS_REGISTER 1

/*struct AtaErrorRegister {
  usize amnf : 1;
  usize tkznf : 1;
  usize abrt : 1;
  usize mcr : 1;
  usize idnf : 1;
  usize mc : 1;
  usize unc : 1;
  usize bbk : 1;
};*/

union AtaDriveHeadRegister {
  struct {
    u8 bits : 4;
    u8 drv : 1;
    u8 one0 : 1; // always 1
    u8 lba : 1;
    u8 one1 : 1; // always 1
  };
  u8 raw;
};

union AtaStatusRegister {
  struct {
    u8 err : 1;
    u8 idx : 1; // always 0
    u8 corr: 1; // always 0
    u8 drq : 1;
    u8 srv : 1; // <
    u8 df : 1; // <
    u8 rdy : 1;
    u8 bsy : 1; // <
  };
  u8 raw;
};

/*struct AtaDeviceControlRegister {
  usize zero : 1; // always 0
  usize nien : 1;
  usize srst : 1;
  usize : 4;
  usize hob : 1;
};

struct DriveAddressRegister {
  usize ds0 : 1;
  usize ds1 : 1;
  usize hs : 4;
  usize wtg : 1;
  usize : 1;
};*/
