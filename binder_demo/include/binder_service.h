#ifndef _LINUX_BINDER_SERVICE_H
#define _LINUX_BINDER_SERVICE_H

#define B_PACK_CHARS(c1, c2, c3, c4) \
	((((c1)<<24)) | (((c2)<<16)) | (((c3)<<8)) | (c4))
#define B_TYPE_LARGE 0x85

enum {
    FIRST_CALL_TRANSACTION  = 0x00000001,
    LAST_CALL_TRANSACTION   = 0x00ffffff,

    PING_TRANSACTION        = B_PACK_CHARS('_','P','N','G'),
    DUMP_TRANSACTION        = B_PACK_CHARS('_','D','M','P'),
    INTERFACE_TRANSACTION   = B_PACK_CHARS('_', 'N', 'T', 'F'),

    // Corresponds to TF_ONE_WAY -- an asynchronous call.
    FLAG_ONEWAY             = 0x00000001
};


struct BinderService
{
    status_t (*transact)(   uint32_t code,
                            const Parcel& data,
                            Parcel* reply,
                            uint32_t flags = 0);
};
#endif /* _LINUX_BINDER_SERVICE_H */
