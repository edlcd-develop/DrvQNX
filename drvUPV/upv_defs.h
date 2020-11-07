#ifndef _UPV_DEFS_H
#define _UPV_DEFS_H

//! Идентификатор устройста PCI-устройства УПВ КЛ
#define UPV_DEVICE_ID 0x0007
//! Идентификатор поставщика PCI-устройства УПВ КЛ 
#define UPV_VENDOR_ID 0x10EE
//! Путь к устройству УПВ КЛ
#define UPV_DEVPATH "/dev/local/upv_kl"
//! Имя устройства УПВ КЛ
#define UPV_DEVNAME "upv_kl"
//! Максимальное кол-во адаптеров УПВ КЛ
#define UPV_MAX_ADAPTERS 8
//! Кол-во каналов ввода Arinc - 429 ввывода Arinc - 429  и РК
#define UPV_REG_CH_IN_AR   48
//! Кол-во каналов ввода РК
#define UPV_REG_CH_IN_RK   48
//! Кол-во каналов вывода Arinc - 429
#define UPV_REG_CH_OUT_AR  48
//! Кол-во каналов вывода РК
#define UPV_REG_CH_OUT_RK  48

/*! Адресное пространство настройки каналов Arinc - 429
 * Channel freq  and pouse set
 * 0 - 48kHz, 4t
 * 1 - 96kHz, 4t
 * 2 - 12,5kHz, 4t
 * 3 - 200kHz, 4t
 * 4 - 48kHz, 8t
 * 5 - 96kHz, 8t
 * 6 - 12,5kHz, 8t
 * 7 - off
*/
#define UPV_REG_START_CH_AR  24823

/*! состояние мезонинов Arinc - 429
 * 0 - мезонин не работает
 * 1 - мезонин запрашивает настройки
 * 2 - настройки мезонина отправлены
*/
#define UPV_REG_STATE_M1_AR  24818
#define UPV_REG_STATE_M2_AR  24819
#define UPV_REG_STATE_M3_AR  24820
#define UPV_REG_STATE_M4_AR  24821

/*! общее состояние
 * 0 - ожидание запросов настроек мезанинов
 * 1 - запросы мезанинов получены, ожидание заполнения настроек
 * 2 - инициирована настройка
 * 3 - чтение регистров и установка констант
 * 4 - отправка настроечных параметров на мезанины
 * 5 - работчий режим
*/
#define UPV_REG_MAIN_STATE   24822

#define UPV_REG_COUNTER_WORD 24576

//! Начало отображеня слов(адрес + данные)
#define UPV_REG_START_OUT_AR_WORD 0x0
//! Участок 32 разрядных слов для выдачи данных
#define UPV_REG_SIZE_IOMEM_PER_CH 256

//! Начало отображеня слов(адрес + данные)
#define UPV_REG_START_IN_AR_WORD 12288

//! Начало учатстка памяти с счетчиками обновления данных
#define UPV_REG_FLAG_UPDATE 24676


#endif /* _UPV_DEFS_H */
