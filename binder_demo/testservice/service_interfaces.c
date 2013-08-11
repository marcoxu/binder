/* Copyright 2008 The Android Open Source Project
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#include "android_filesystem_config.h"

#include "binder.h"

#if 0
#define LOGI(x...) fprintf(stderr, "svcmgr: " x)
#define LOGE(x...) fprintf(stderr, "svcmgr: " x)
#else
#define LOGE printf
#define LOGI printf
#define LOG_TAG "ServiceManager"
#endif

static int gSingleProcess = 0;
//sp<IServiceManager> gDefaultServiceManager;
static int  DriverFD = 0;
const int FIRST_CALL_TRANSACTION  = 0x00000001;
const int ADD_SERVICE_TRANSACTION = 0x00000003;
const int NO_ERROR = 0;
unsigned int transactData[20];
#define ALIGN(x, a) __ALIGN_MASK(x, (typeof(x))(a) - 1)
#define __ALIGN_MASK(x, mask) (((x) + (mask))&~(mask))

static int open_driver()
{
    if (gSingleProcess) {
        return -1;
    }

    int fd = open("/dev/binder", O_RDWR);
    if (fd >= 0) {
        fcntl(fd, F_SETFD, FD_CLOEXEC);
        int vers;

        int result = ioctl(fd, BINDER_VERSION, &vers);

        if (result == -1) {
            LOGE("Binder ioctl to obtain version failed: %s", strerror(errno));
            close(fd);
            fd = -1;
        }
        if (result != 0 || vers != BINDER_CURRENT_PROTOCOL_VERSION) {
            LOGE("Binder driver protocol does not match user space protocol!");
            close(fd);
            fd = -1;
        }

        int maxThreads = 15;
        result = ioctl(fd, BINDER_SET_MAX_THREADS, &maxThreads);
        if (result == -1) {
            LOGE("Binder ioctl to set max threads failed: %s", strerror(errno));
        }
        
    } else {
        LOGI("Opening '/dev/binder' failed: %s\n", strerror(errno));
    }
    return fd;
}

//sp<IServiceManager> defaultServiceManager()
//{
//    if (gDefaultServiceManager != NULL) return gDefaultServiceManager;
//    
//    {
//        AutoMutex _l(gDefaultServiceManagerLock);
//        if (gDefaultServiceManager == NULL) {
//            gDefaultServiceManager = interface_cast<IServiceManager>(
//                ProcessState::self()->getContextObject(NULL));
//        }
//    }
//    
//    return gDefaultServiceManager;
//}
//
//int transact(int handle,
//             int code, const Parcel& data,
//             Parcel* reply, int flags)
//{
//    int err = data.errorCheck();
//
//    flags |= TF_ACCEPT_FDS;
//
//    if (err == 0) {
//        printf(">>>> SEND from pid %d uid %d %s\n", getpid(), getuid(),
//            (flags & TF_ONE_WAY) == 0 ? "READ REPLY" : "ONE WAY");
//        err = writeTransactionData(BC_TRANSACTION, flags, handle, code, data, NULL);
//    }
//    
//    if (err != NO_ERROR) {
//        if (reply) reply->setError(err);
//        return (mLastError = err);
//    }
//    
//    if ((flags & TF_ONE_WAY) == 0) {
//        if (reply) {
//            err = waitForResponse(reply);
//        } else {
//            Parcel fakeReply;
//            err = waitForResponse(&fakeReply);
//        }
//        
//    } else {
//        err = waitForResponse(NULL, NULL);
//    }
//    
//    return err;
//}

//int writeTransactionData(int cmd, int binderFlags,
//    int handle, int code, const Parcel& data, int* statusBuffer)
//{
//    binder_transaction_data tr;
//
//    tr.target.handle = handle;
//    tr.code = code;
//    tr.flags = binderFlags;
//    
//    const status_t err = data.errorCheck();
//    if (err == NO_ERROR) {
//        tr.data_size = data.ipcDataSize();
//        tr.data.ptr.buffer = data.ipcData();
//        tr.offsets_size = data.ipcObjectsCount()*sizeof(int);
//        tr.data.ptr.offsets = data.ipcObjects();
//    } else if (statusBuffer) {
//        tr.flags |= TF_STATUS_CODE;
//        *statusBuffer = err;
//        tr.data_size = sizeof(status_t);
//        tr.data.ptr.buffer = statusBuffer;
//        tr.offsets_size = 0;
//        tr.data.ptr.offsets = NULL;
//    } else {
//        return (mLastError = err);
//    }
//    
//    mOut.writeInt32(cmd);
//    mOut.write(&tr, sizeof(tr));
//    
//    return NO_ERROR;
//}

int talkWithDriver(int doReceive)
{
    //LOG_ASSERT(DriverFD >= 0, "Binder driver is not opened");
    
    struct binder_write_read bwr;
    struct binder_transaction_data tr;
    struct flat_binder_object obj;
    char binderData[250];
    size_t nameLen = strlen("default");
    size_t objLen = ALIGN(sizeof(size_t)+strlen("default")+1+sizeof(size_t), sizeof(void *));

    tr.target.handle = 0x0;
    tr.code = 0x0;
    tr.flags = 0;
    
    
    obj.flags = 0x7f | 0x100;
    obj.type = BINDER_TYPE_BINDER;
    obj.binder = NULL;
    obj.cookie = NULL;
    
    memcpy((void*)binderData, &nameLen, sizeof(size_t));
    memcpy((void*)(binderData+sizeof(size_t)), "default", strlen("default")+1);
    memcpy((void*)(binderData+ALIGN(sizeof(size_t)+strlen("default")+1, sizeof(void *))), &objLen, sizeof(size_t));
    memcpy((void*)(binderData+ALIGN(sizeof(size_t)+strlen("default")+1, sizeof(void *))+sizeof(size_t)), &obj, sizeof(struct flat_binder_object));
    
    tr.data_size = ALIGN(ALIGN(sizeof(size_t)+strlen("default")+1, sizeof(void *))+sizeof(size_t)+sizeof(struct flat_binder_object), sizeof(void *));
    tr.data.ptr.buffer = binderData;
    tr.offsets_size = ALIGN(sizeof(struct flat_binder_object)+sizeof(size_t), sizeof(size_t));
    tr.data.ptr.offsets = binderData+ALIGN(sizeof(size_t)+strlen("default")+1, sizeof(void *));
    printf("tr.type 0x%08x%08x\n", (int)(obj.type>>32), (int)obj.type);
    printf("tr.data_size 0x%08x%08x\n", (int)(tr.data_size>>32), (int)tr.data_size);
    printf("tr.tr.data.ptr.buffer %p\n", tr.data.ptr.buffer);
    printf("tr.offsets_size 0x%08x%08x\n", (int)(tr.offsets_size>>32), (int)tr.offsets_size);
    printf("tr.tr.data.ptr.offsets %p\n", tr.data.ptr.offsets);
    
    transactData[0] = BC_TRANSACTION;
    memcpy((void *)&transactData[1], &tr, sizeof(tr));
    bwr.write_size = sizeof(tr) + 4; //outAvail;
    bwr.write_buffer = (unsigned long)transactData;

    // Return immediately if there is nothing to do.
    if ((bwr.write_size == 0) && (bwr.read_size == 0)) return NO_ERROR;
    
    bwr.write_consumed = 0;
    bwr.read_consumed = 0;
    int err;
    do {
        if (ioctl(DriverFD, BINDER_WRITE_READ, &bwr) >= 0)
            err = NO_ERROR;
        else
            err = -errno;
    } while (err == -EINTR);

    // Is the read buffer empty?
    //const bool needRead = mIn.dataPosition() >= mIn.dataSize();
    
    // We don't want to write anything if we are still reading
    // from data left in the input buffer and the caller
    // has requested to read the next data.
    // const int outAvail = (!doReceive || needRead) ? mOut.dataSize() : 0;

    tr.target.handle = 0x123456;
    tr.code = 0xff;
    tr.flags = 0;
    
    tr.data_size = 0;
    tr.data.ptr.buffer = NULL;
    tr.offsets_size = 0;
    tr.data.ptr.offsets = 0;
    
    transactData[0] = BC_TRANSACTION;
    memcpy((void *)&transactData[1], &tr, sizeof(tr));
    //transactData[1] = 1;
    //transactData[2] = 2;
    //transactData[3] = 3;
    bwr.write_size = sizeof(tr) + 4; //outAvail;
    bwr.write_buffer = (unsigned long)transactData;

    // This is what we'll read.
    //if (doReceive && needRead) {
    //    bwr.read_size = mIn.dataCapacity();
    //    bwr.read_buffer = (long unsigned int)mIn.data();
    //} else {
    //    bwr.read_size = 0;
    //}
    
    // Return immediately if there is nothing to do.
    if ((bwr.write_size == 0) && (bwr.read_size == 0)) return NO_ERROR;
    
    bwr.write_consumed = 0;
    bwr.read_consumed = 0;
    do {
        if (ioctl(DriverFD, BINDER_WRITE_READ, &bwr) >= 0)
            err = NO_ERROR;
        else
            err = -errno;
    } while (err == -EINTR);

    if (err >= NO_ERROR) {
//        if (bwr.write_consumed > 0) {
//            if (bwr.write_consumed < (sint)mOut.dataSize())
//                mOut.remove(0, bwr.write_consumed);
//            else
//                mOut.setDataSize(0);
//        }
//        if (bwr.read_consumed > 0) {
//            mIn.setDataSize(bwr.read_consumed);
//            mIn.setDataPosition(0);
//        }
//        return NO_ERROR;
    }
    
    printf("talkWithDriver: error %d\n", err);
    return err;
}

int main(int argc, char **argv)
{
    struct binder_state *bs;
    void *svcmgr = BINDER_SERVICE_MANAGER;

    printf("open_driver start\n");
    DriverFD = open_driver();
    printf("open_driver done\n");

    printf("talkWithDriver start\n");
    talkWithDriver(0);
    printf("talkWithDriver done\n");
    return 0;
}
