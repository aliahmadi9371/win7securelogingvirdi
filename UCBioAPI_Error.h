#ifndef _UCBioAPI_ERROR_H
#define _UCBioAPI_ERROR_H

#define UCBioAPIERROR_NONE						(0)

#define UCBioAPIERROR_BASE_GENERAL				(0x0000)
#define UCBioAPIERROR_BASE_INIT					(0x0100)
#define UCBioAPIERROR_BASE_DEVICE				(0x0200)
#define UCBioAPIERROR_BASE_UI					(0x0300)
#define UCBioAPIERROR_BASE_FASTSEARCH			(0x0400)
#define UCBioAPIERROR_BASE_OPTIONAL				(0x0500)
#define UCBioAPIERROR_BASE_SMARTCARD			(0x0600)
#define UCBioAPIERROR_BASE_FPLIB				(0x0700)

#define UCBioAPIERROR_FPLIB_QUALITY_POOR		(UCBioAPIERROR_BASE_FPLIB + 0xa1) // a1 ���� �� �̻��� FPLIB���� ���������Ͽ� ����� by kks

#define UCBioAPIERROR_INVALID_HANDLE             (UCBioAPIERROR_BASE_GENERAL + 0x01)
#define UCBioAPIERROR_INVALID_POINTER            (UCBioAPIERROR_BASE_GENERAL + 0x02)
#define UCBioAPIERROR_INVALID_TYPE               (UCBioAPIERROR_BASE_GENERAL + 0x03)
#define UCBioAPIERROR_FUNCTION_FAIL              (UCBioAPIERROR_BASE_GENERAL + 0x04)
#define UCBioAPIERROR_STRUCTTYPE_NOT_MATCHED     (UCBioAPIERROR_BASE_GENERAL + 0x05)
#define UCBioAPIERROR_ALREADY_PROCESSED          (UCBioAPIERROR_BASE_GENERAL + 0x06)
#define UCBioAPIERROR_EXTRACTION_OPEN_FAIL       (UCBioAPIERROR_BASE_GENERAL + 0x07)
#define UCBioAPIERROR_VERIFICATION_OPEN_FAIL     (UCBioAPIERROR_BASE_GENERAL + 0x08)
#define UCBioAPIERROR_DATA_PROCESS_FAIL          (UCBioAPIERROR_BASE_GENERAL + 0x09)
#define UCBioAPIERROR_MUST_BE_PROCESSED_DATA     (UCBioAPIERROR_BASE_GENERAL + 0x0a)
#define UCBioAPIERROR_INTERNAL_CHECKSUM_FAIL     (UCBioAPIERROR_BASE_GENERAL + 0x0b)
#define UCBioAPIERROR_ENCRYPTED_DATA_ERROR       (UCBioAPIERROR_BASE_GENERAL + 0x0c) 
#define UCBioAPIERROR_UNKNOWN_FORMAT             (UCBioAPIERROR_BASE_GENERAL + 0x0d) 
#define UCBioAPIERROR_UNKNOWN_VERSION            (UCBioAPIERROR_BASE_GENERAL + 0x0e) 
#define UCBioAPIERROR_VALIDITY_FAIL              (UCBioAPIERROR_BASE_GENERAL + 0x0f) 
#define UCBioAPIERROR_INVALID_TEMPLATESIZE       (UCBioAPIERROR_BASE_GENERAL + 0x10) 
#define UCBioAPIERROR_INVALID_TEMPLATE           (UCBioAPIERROR_BASE_GENERAL + 0x11)
#define UCBioAPIERROR_EXPIRED_VERSION            (UCBioAPIERROR_BASE_GENERAL + 0x12)
#define UCBioAPIERROR_INVALID_SAMPLESPERFINGER   (UCBioAPIERROR_BASE_GENERAL + 0x13)
#define UCBioAPIERROR_UNKNOWN_INPUTFORMAT        (UCBioAPIERROR_BASE_GENERAL + 0x14)
#define UCBioAPIERROR_INVALID_PARAMETER          (UCBioAPIERROR_BASE_GENERAL + 0x15)
#define UCBioAPIERROR_FUNCTION_NOT_SUPPORTED     (UCBioAPIERROR_BASE_GENERAL + 0x16)

#define UCBioAPIERROR_INIT_MAXFINGERSFORENROLL   (UCBioAPIERROR_BASE_INIT + 0x01) 
#define UCBioAPIERROR_INIT_NECESSARYENROLLNUM    (UCBioAPIERROR_BASE_INIT + 0x02)
#define UCBioAPIERROR_INIT_SAMPLESPERFINGER      (UCBioAPIERROR_BASE_INIT + 0x03) 
#define UCBioAPIERROR_INIT_SECULEVELFORENROLL    (UCBioAPIERROR_BASE_INIT + 0x04)
#define UCBioAPIERROR_INIT_SECULEVELFORVERIFY    (UCBioAPIERROR_BASE_INIT + 0x05)
#define UCBioAPIERROR_INIT_SECULEVELFORIDENTIFY  (UCBioAPIERROR_BASE_INIT + 0x06) 
#define UCBioAPIERROR_INIT_RESERVED1             (UCBioAPIERROR_BASE_INIT + 0x07)
#define UCBioAPIERROR_INIT_RESERVED2             (UCBioAPIERROR_BASE_INIT + 0x08)
#define UCBioAPIERROR_INIT_TEMPLATE_FORMAT		 (UCBioAPIERROR_BASE_INIT + 0x09)
#define UCBioAPIERROR_INIT_LIVEDETECTLEVEL		 (UCBioAPIERROR_BASE_INIT + 0x0a)

#define UCBioAPIERROR_DEVICE_OPEN_FAIL           (UCBioAPIERROR_BASE_DEVICE + 0x01)
#define UCBioAPIERROR_INVALID_DEVICE_ID          (UCBioAPIERROR_BASE_DEVICE + 0x02)
#define UCBioAPIERROR_WRONG_DEVICE_ID            (UCBioAPIERROR_BASE_DEVICE + 0x03)
#define UCBioAPIERROR_DEVICE_ALREADY_OPENED      (UCBioAPIERROR_BASE_DEVICE + 0x04)
#define UCBioAPIERROR_DEVICE_NOT_OPENED          (UCBioAPIERROR_BASE_DEVICE + 0x05)
#define UCBioAPIERROR_DEVICE_BRIGHTNESS          (UCBioAPIERROR_BASE_DEVICE + 0x06)
#define UCBioAPIERROR_DEVICE_CONTRAST            (UCBioAPIERROR_BASE_DEVICE + 0x07)
#define UCBioAPIERROR_DEVICE_GAIN                (UCBioAPIERROR_BASE_DEVICE + 0x08)

#define UCBioAPIERROR_USER_CANCEL                (UCBioAPIERROR_BASE_UI + 0x01)
#define UCBioAPIERROR_USER_BACK                  (UCBioAPIERROR_BASE_UI + 0x02)
#define UCBioAPIERROR_CAPTURE_TIMEOUT            (UCBioAPIERROR_BASE_UI + 0x03)
#define UCBioAPIERROR_CAPTURE_FAKE_SUSPICIOUS    (UCBioAPIERROR_BASE_UI + 0x04)
#define UCBioAPIERROR_ENROLL_EVENT_PLACE         (UCBioAPIERROR_BASE_UI + 0x05)
#define UCBioAPIERROR_ENROLL_EVENT_HOLD          (UCBioAPIERROR_BASE_UI + 0x06)
#define UCBioAPIERROR_ENROLL_EVENT_REMOVE        (UCBioAPIERROR_BASE_UI + 0x07)
#define UCBioAPIERROR_ENROLL_EVENT_PLACE_AGAIN   (UCBioAPIERROR_BASE_UI + 0x08)
#define UCBioAPIERROR_ENROLL_EVENT_PROCESS       (UCBioAPIERROR_BASE_UI + 0x09)
#define UCBioAPIERROR_ENROLL_EVENT_MATCH_FAILED  (UCBioAPIERROR_BASE_UI + 0x0a)

#define UCBioAPIERROR_FASTSEARCH_INIT_FAIL       (UCBioAPIERROR_BASE_FASTSEARCH + 0x01)
#define UCBioAPIERROR_FASTSEARCH_SAVE_DB         (UCBioAPIERROR_BASE_FASTSEARCH + 0x02)
#define UCBioAPIERROR_FASTSEARCH_LOAD_DB         (UCBioAPIERROR_BASE_FASTSEARCH + 0x03)
#define UCBioAPIERROR_FASTSEARCH_UNKNOWN_VER     (UCBioAPIERROR_BASE_FASTSEARCH + 0x04)
#define UCBioAPIERROR_FASTSEARCH_IDENTIFY_FAIL   (UCBioAPIERROR_BASE_FASTSEARCH + 0x05)
#define UCBioAPIERROR_FASTSEARCH_DUPLICATED_ID   (UCBioAPIERROR_BASE_FASTSEARCH + 0x06)
#define UCBioAPIERROR_FASTSEARCH_IDENTIFY_STOP   (UCBioAPIERROR_BASE_FASTSEARCH + 0x07)
#define UCBioAPIERROR_FASTSEARCH_NOUSER_EXIST    (UCBioAPIERROR_BASE_FASTSEARCH + 0x08)

#define UCBioAPIERROR_OPTIONAL_UUID_FAIL         (UCBioAPIERROR_BASE_OPTIONAL + 0x01)
#define UCBioAPIERROR_OPTIONAL_PIN1_FAIL         (UCBioAPIERROR_BASE_OPTIONAL + 0x02)
#define UCBioAPIERROR_OPTIONAL_PIN2_FAIL         (UCBioAPIERROR_BASE_OPTIONAL + 0x03)
#define UCBioAPIERROR_OPTIONAL_SITEID_FAIL       (UCBioAPIERROR_BASE_OPTIONAL + 0x04)
#define UCBioAPIERROR_OPTIONAL_EXPIRE_DATE_FAIL  (UCBioAPIERROR_BASE_OPTIONAL + 0x05)

#define UCBioAPIERROR_SC_FUNCTION_FAILED         (UCBioAPIERROR_BASE_SMARTCARD + 0x01)
#define UCBioAPIERROR_SC_NOT_SUPPORTED_DEVICE    (UCBioAPIERROR_BASE_SMARTCARD + 0x02)
#define UCBioAPIERROR_SC_NOT_SUPPORTED_FIRMWARE  (UCBioAPIERROR_BASE_SMARTCARD + 0x03)

#endif/*_UCBioAPI_ERROR_H */