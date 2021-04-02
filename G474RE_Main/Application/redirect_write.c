/*
 * redirect_write.c
 *
 *  Created on: Apr 2, 2021
 *      Author: chris
 */
#include <SEGGER_RTT.h>

int _write(int file, char *ptr, int len) {
  (void) file;  /// Not used, avoid warning
  SEGGER_RTT_Write(0, ptr, len);
  return len;
}

