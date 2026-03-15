/* AUTO-GENERATED dispatch table. DO NOT EDIT. */
#include "nes_runtime.h"
extern int g_current_bank;

void call_by_address(uint16_t addr) {
    switch (addr) {
        case 0xC913:
            func_C913(); break;
        case 0xC999:
            func_C999(); break;
        case 0xC9D5:
            func_C9D5(); break;
        case 0x8000:
            switch (g_current_bank) {
                case 15: func_C000(); break;
                case 0: func_8000_b0(); break;
                case 2: func_8000_b2(); break;
                case 5: func_8000_b5(); break;
                case 10: func_8000_b10(); break;
                case 12: func_8000_b12(); break;
                case 13: func_8000_b13(); break;
                case 14: func_8000_b14(); break;
                case 1: func_8000_b1(); break;
                case 3: func_8000_b3(); break;
                case 4: func_8000_b4(); break;
                case 6: func_8000_b6(); break;
                case 7: func_8000_b7(); break;
                case 8: func_8000_b8(); break;
                case 9: func_8000_b9(); break;
                case 11: func_8000_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xCBBF:
            func_CBBF(); break;
        case 0xCA78:
            func_CA78(); break;
        case 0xDA6A:
            func_DA6A(); break;
        case 0xC989:
            func_C989(); break;
        case 0xC95D:
            func_C95D(); break;
        case 0xC9D6:
            func_C9D6(); break;
        case 0xCC85:
            func_CC85(); break;
        case 0x8009:
            switch (g_current_bank) {
                case 15: func_C009(); break;
                case 0: func_8009_b0(); break;
                case 1: func_8009_b1(); break;
                case 2: func_8009_b2(); break;
                case 3: func_8009_b3(); break;
                case 4: func_8009_b4(); break;
                case 5: func_8009_b5(); break;
                case 6: func_8009_b6(); break;
                case 7: func_8009_b7(); break;
                case 8: func_8009_b8(); break;
                case 9: func_8009_b9(); break;
                case 10: func_8009_b10(); break;
                case 11: func_8009_b11(); break;
                case 12: func_8009_b12(); break;
                case 13: func_8009_b13(); break;
                case 14: func_8009_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8003:
            switch (g_current_bank) {
                case 15: func_C003(); break;
                case 0: func_8003_b0(); break;
                case 1: func_8003_b1(); break;
                case 2: func_8003_b2(); break;
                case 3: func_8003_b3(); break;
                case 4: func_8003_b4(); break;
                case 5: func_8003_b5(); break;
                case 6: func_8003_b6(); break;
                case 7: func_8003_b7(); break;
                case 8: func_8003_b8(); break;
                case 9: func_8003_b9(); break;
                case 10: func_8003_b10(); break;
                case 11: func_8003_b11(); break;
                case 12: func_8003_b12(); break;
                case 13: func_8003_b13(); break;
                case 14: func_8003_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xCA35:
            func_CA35(); break;
        case 0x8681:
            switch (g_current_bank) {
                case 5: func_8681_b5(); break;
                case 10: func_8681_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8151:
            func_8151_b14(); break;
        case 0x8040:
            switch (g_current_bank) {
                case 15: func_C040(); break;
                case 14: func_8040_b14(); break;
                case 4: func_8040_b4(); break;
                case 8: func_8040_b8(); break;
                case 10: func_8040_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA66B:
            func_A66B_b14(); break;
        case 0x8804:
            func_8804_b14(); break;
        case 0x8ADC:
            func_8ADC_b14(); break;
        case 0x8A08:
            switch (g_current_bank) {
                case 14: func_8A08_b14(); break;
                case 11: func_8A08_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x877C:
            switch (g_current_bank) {
                case 14: func_877C_b14(); break;
                case 0: func_877C_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x890A:
            func_890A_b14(); break;
        case 0x8BD2:
            func_8BD2_b14(); break;
        case 0x8494:
            switch (g_current_bank) {
                case 14: func_8494_b14(); break;
                case 0: func_8494_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xCBD0:
            func_CBD0(); break;
        case 0xCC1A:
            func_CC1A(); break;
        case 0xCB4F:
            func_CB4F(); break;
        case 0xCABC:
            func_CABC(); break;
        case 0x8006:
            switch (g_current_bank) {
                case 0: func_8006_b0(); break;
                case 1: func_8006_b1(); break;
                case 2: func_8006_b2(); break;
                case 3: func_8006_b3(); break;
                case 4: func_8006_b4(); break;
                case 5: func_8006_b5(); break;
                case 6: func_8006_b6(); break;
                case 7: func_8006_b7(); break;
                case 8: func_8006_b8(); break;
                case 9: func_8006_b9(); break;
                case 10: func_8006_b10(); break;
                case 11: func_8006_b11(); break;
                case 12: func_8006_b12(); break;
                case 13: func_8006_b13(); break;
                case 14: func_8006_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xCB2F:
            func_CB2F(); break;
        case 0xB7AE:
            switch (g_current_bank) {
                case 0: func_B7AE_b0(); break;
                case 1: func_B7AE_b1(); break;
                case 2: func_B7AE_b2(); break;
                case 3: func_B7AE_b3(); break;
                case 4: func_B7AE_b4(); break;
                case 5: func_B7AE_b5(); break;
                case 6: func_B7AE_b6(); break;
                case 7: func_B7AE_b7(); break;
                case 8: func_B7AE_b8(); break;
                case 9: func_B7AE_b9(); break;
                case 10: func_B7AE_b10(); break;
                case 11: func_B7AE_b11(); break;
                case 12: func_B7AE_b12(); break;
                case 13: func_B7AE_b13(); break;
                case 14: func_B7AE_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xDA7D:
            func_DA7D(); break;
        case 0xFC65:
            func_FC65(); break;
        case 0xC970:
            func_C970(); break;
        case 0xC9D0:
            func_C9D0(); break;
        case 0xD61D:
            func_D61D(); break;
        case 0xCF3C:
            func_CF3C(); break;
        case 0xC9FA:
            func_C9FA(); break;
        case 0x800D:
            switch (g_current_bank) {
                case 15: func_C00D(); break;
                case 5: func_800D_b5(); break;
                case 4: func_800D_b4(); break;
                case 6: func_800D_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xD0D0:
            func_D0D0(); break;
        case 0xA0A0:
            switch (g_current_bank) {
                case 7: func_A0A0_b7(); break;
                case 10: func_A0A0_b10(); break;
                case 14: func_A0A0_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xE020:
            func_E020(); break;
        case 0xC060:
            func_C060(); break;
        case 0xD000:
            func_D000(); break;
        case 0xE860:
            func_E860(); break;
        case 0xFFC9:
            func_FFC9(); break;
        case 0x871F:
            func_871F_b11(); break;
        case 0xFFFF:
            func_FFFF(); break;
        case 0xFF8C:
            func_FF8C(); break;
        case 0xFF66:
            func_FF66(); break;
        case 0x862F:
            func_862F_b5(); break;
        case 0x804A:
            func_804A_b5(); break;
        case 0x8011:
            func_8011_b14(); break;
        case 0xA6BC:
            func_A6BC_b14(); break;
        case 0xA8C8:
            func_A8C8_b14(); break;
        case 0x87CA:
            switch (g_current_bank) {
                case 14: func_87CA_b14(); break;
                case 3: func_87CA_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x88CB:
            func_88CB_b14(); break;
        case 0x88C6:
            func_88C6_b14(); break;
        case 0xD0E4:
            func_D0E4(); break;
        case 0x8B87:
            func_8B87_b14(); break;
        case 0xABEC:
            func_ABEC_b14(); break;
        case 0xABF1:
            func_ABF1_b14(); break;
        case 0x8AD7:
            func_8AD7_b14(); break;
        case 0x81A7:
            func_81A7_b14(); break;
        case 0x8A51:
            switch (g_current_bank) {
                case 14: func_8A51_b14(); break;
                case 4: func_8A51_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB927:
            func_B927_b14(); break;
        case 0x87DC:
            switch (g_current_bank) {
                case 14: func_87DC_b14(); break;
                case 12: func_87DC_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8909:
            func_8909_b14(); break;
        case 0x8B9A:
            func_8B9A_b14(); break;
        case 0x8BC0:
            switch (g_current_bank) {
                case 15: func_CBC0(); break;
                case 14: func_8BC0_b14(); break;
                case 11: func_8BC0_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xF859:
            func_F859(); break;
        case 0x8242:
            switch (g_current_bank) {
                case 12: func_8242_b12(); break;
                case 4: func_8242_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C1A:
            func_8C1A_b14(); break;
        case 0x849A:
            func_849A_b14(); break;
        case 0x84C4:
            func_84C4_b14(); break;
        case 0xCC1D:
            func_CC1D(); break;
        case 0xCAB5:
            func_CAB5(); break;
        case 0xCAED:
            func_CAED(); break;
        case 0x801B:
            func_801B_b5(); break;
        case 0xF0DB:
            func_F0DB(); break;
        case 0xD571:
            func_D571(); break;
        case 0xB2CC:
            switch (g_current_bank) {
                case 0: func_B2CC_b0(); break;
                case 1: func_B2CC_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xFB22:
            func_FB22(); break;
        case 0xEBBF:
            func_EBBF(); break;
        case 0xC058:
            func_C058(); break;
        case 0xCFDC:
            func_CFDC(); break;
        case 0xF990:
            func_F990(); break;
        case 0xF9E7:
            func_F9E7(); break;
        case 0xCFFB:
            func_CFFB(); break;
        case 0xF975:
            func_F975(); break;
        case 0xC0BD:
            func_C0BD(); break;
        case 0xFA85:
            func_FA85(); break;
        case 0xFA75:
            func_FA75(); break;
        case 0xC4CA:
            func_C4CA(); break;
        case 0xCD6F:
            func_CD6F(); break;
        case 0xC199:
            func_C199(); break;
        case 0xC154:
            func_C154(); break;
        case 0xC205:
            func_C205(); break;
        case 0xC1C5:
            func_C1C5(); break;
        case 0xF3D6:
            func_F3D6(); break;
        case 0xC25B:
            func_C25B(); break;
        case 0xC27C:
            func_C27C(); break;
        case 0xCDB5:
            func_CDB5(); break;
        case 0xCFF4:
            func_CFF4(); break;
        case 0xC315:
            func_C315(); break;
        case 0xE86C:
            func_E86C(); break;
        case 0xE8C3:
            func_E8C3(); break;
        case 0xC37A:
            func_C37A(); break;
        case 0xF057:
            func_F057(); break;
        case 0xC393:
            func_C393(); break;
        case 0xC37D:
            func_C37D(); break;
        case 0xC8DC:
            func_C8DC(); break;
        case 0xC07B:
            func_C07B(); break;
        case 0xDC46:
            func_DC46(); break;
        case 0xCA25:
            func_CA25(); break;
        case 0xCBA8:
            func_CBA8(); break;
        case 0xC0D9:
            func_C0D9(); break;
        case 0xC4BF:
            func_C4BF(); break;
        case 0xB731:
            func_B731_b7(); break;
        case 0xCAF7:
            func_CAF7(); break;
        case 0xE0AA:
            func_E0AA(); break;
        case 0xBA55:
            switch (g_current_bank) {
                case 15: func_FA55(); break;
                case 0: func_BA55_b0(); break;
                case 1: func_BA55_b1(); break;
                case 2: func_BA55_b2(); break;
                case 3: func_BA55_b3(); break;
                case 4: func_BA55_b4(); break;
                case 5: func_BA55_b5(); break;
                case 6: func_BA55_b6(); break;
                case 7: func_BA55_b7(); break;
                case 8: func_BA55_b8(); break;
                case 9: func_BA55_b9(); break;
                case 10: func_BA55_b10(); break;
                case 11: func_BA55_b11(); break;
                case 12: func_BA55_b12(); break;
                case 13: func_BA55_b13(); break;
                case 14: func_BA55_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xCE80:
            func_CE80(); break;
        case 0x9E21:
            switch (g_current_bank) {
                case 12: func_9E21_b12(); break;
                case 3: func_9E21_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9F44:
            func_9F44_b12(); break;
        case 0x909D:
            func_909D_b12(); break;
        case 0x95B1:
            func_95B1_b12(); break;
        case 0xDB0A:
            func_DB0A(); break;
        case 0xA79A:
            func_A79A_b12(); break;
        case 0x9570:
            func_9570_b12(); break;
        case 0xDB26:
            func_DB26(); break;
        case 0xCF3B:
            func_CF3B(); break;
        case 0x8106:
            func_8106_b5(); break;
        case 0xD0C8:
            func_D0C8(); break;
        case 0xD090:
            func_D090(); break;
        case 0x8A93:
            func_8A93_b12(); break;
        case 0x86EF:
            switch (g_current_bank) {
                case 11: func_86EF_b11(); break;
                case 0: func_86EF_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8626:
            func_8626_b5(); break;
        case 0xF36F:
            func_F36F(); break;
        case 0xF957:
            func_F957(); break;
        case 0xABF8:
            func_ABF8_b14(); break;
        case 0xABF6:
            func_ABF6_b14(); break;
        case 0x89D5:
            func_89D5_b14(); break;
        case 0xC08E:
            func_C08E(); break;
        case 0xF24D:
            func_F24D(); break;
        case 0x821F:
            func_821F_b12(); break;
        case 0x81E2:
            func_81E2_b12(); break;
        case 0x87A4:
            switch (g_current_bank) {
                case 12: func_87A4_b12(); break;
                case 4: func_87A4_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C7F:
            func_8C7F_b14(); break;
        case 0x8710:
            func_8710_b14(); break;
        case 0xF181:
            func_F181(); break;
        case 0xF228:
            func_F228(); break;
        case 0xF0F1:
            func_F0F1(); break;
        case 0xF845:
            func_F845(); break;
        case 0xFB20:
            func_FB20(); break;
        case 0xCFCA:
            func_CFCA(); break;
        case 0xFA06:
            func_FA06(); break;
        case 0xFAD6:
            func_FAD6(); break;
        case 0xF78C:
            func_F78C(); break;
        case 0xC193:
            func_C193(); break;
        case 0xCD78:
            func_CD78(); break;
        case 0xDC45:
            func_DC45(); break;
        case 0xB982:
            switch (g_current_bank) {
                case 0: func_B982_b0(); break;
                case 1: func_B982_b1(); break;
                case 2: func_B982_b2(); break;
                case 3: func_B982_b3(); break;
                case 4: func_B982_b4(); break;
                case 5: func_B982_b5(); break;
                case 6: func_B982_b6(); break;
                case 7: func_B982_b7(); break;
                case 8: func_B982_b8(); break;
                case 9: func_B982_b9(); break;
                case 10: func_B982_b10(); break;
                case 11: func_B982_b11(); break;
                case 12: func_B982_b12(); break;
                case 13: func_B982_b13(); break;
                case 14: func_B982_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xEBEE:
            func_EBEE(); break;
        case 0xB7D6:
            switch (g_current_bank) {
                case 0: func_B7D6_b0(); break;
                case 1: func_B7D6_b1(); break;
                case 2: func_B7D6_b2(); break;
                case 3: func_B7D6_b3(); break;
                case 4: func_B7D6_b4(); break;
                case 5: func_B7D6_b5(); break;
                case 6: func_B7D6_b6(); break;
                case 7: func_B7D6_b7(); break;
                case 8: func_B7D6_b8(); break;
                case 9: func_B7D6_b9(); break;
                case 10: func_B7D6_b10(); break;
                case 11: func_B7D6_b11(); break;
                case 12: func_B7D6_b12(); break;
                case 13: func_B7D6_b13(); break;
                case 14: func_B7D6_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8070:
            switch (g_current_bank) {
                case 0: func_8070_b0(); break;
                case 1: func_8070_b1(); break;
                case 2: func_8070_b2(); break;
                case 3: func_8070_b3(); break;
                case 4: func_8070_b4(); break;
                case 5: func_8070_b5(); break;
                case 6: func_8070_b6(); break;
                case 7: func_8070_b7(); break;
                case 8: func_8070_b8(); break;
                case 9: func_8070_b9(); break;
                case 10: func_8070_b10(); break;
                case 11: func_8070_b11(); break;
                case 12: func_8070_b12(); break;
                case 13: func_8070_b13(); break;
                case 14: func_8070_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB9E8:
            func_B9E8_b0(); break;
        case 0xBE00:
            switch (g_current_bank) {
                case 4: func_BE00_b4(); break;
                case 3: func_BE00_b3(); break;
                case 5: func_BE00_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9808:
            switch (g_current_bank) {
                case 4: func_9808_b4(); break;
                case 3: func_9808_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB42A:
            func_B42A_b4(); break;
        case 0xD7C5:
            func_D7C5(); break;
        case 0xC658:
            func_C658(); break;
        case 0xC8CD:
            func_C8CD(); break;
        case 0xC810:
            func_C810(); break;
        case 0xC6EA:
            func_C6EA(); break;
        case 0xC6D8:
            func_C6D8(); break;
        case 0xC6D0:
            func_C6D0(); break;
        case 0xC6BE:
            func_C6BE(); break;
        case 0xC826:
            func_C826(); break;
        case 0xC83C:
            func_C83C(); break;
        case 0xC87A:
            func_C87A(); break;
        case 0xC864:
            func_C864(); break;
        case 0xC609:
            func_C609(); break;
        case 0xF89E:
            func_F89E(); break;
        case 0xFCB9:
            func_FCB9(); break;
        case 0x9E0E:
            func_9E0E_b12(); break;
        case 0xD03B:
            func_D03B(); break;
        case 0xCB27:
            func_CB27(); break;
        case 0xFCA7:
            func_FCA7(); break;
        case 0xFCB2:
            func_FCB2(); break;
        case 0xF3A5:
            func_F3A5(); break;
        case 0x9405:
            func_9405_b12(); break;
        case 0x9850:
            func_9850_b12(); break;
        case 0x95E9:
            func_95E9_b12(); break;
        case 0x9341:
            func_9341_b12(); break;
        case 0x9185:
            func_9185_b12(); break;
        case 0x9181:
            switch (g_current_bank) {
                case 12: func_9181_b12(); break;
                case 10: func_9181_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9140:
            func_9140_b12(); break;
        case 0x9312:
            func_9312_b12(); break;
        case 0xC6AF:
            func_C6AF(); break;
        case 0xDD61:
            func_DD61(); break;
        case 0xDAAF:
            func_DAAF(); break;
        case 0xDB45:
            func_DB45(); break;
        case 0xA730:
            func_A730_b12(); break;
        case 0xA813:
            func_A813_b12(); break;
        case 0xAA83:
            func_AA83_b12(); break;
        case 0xA7CF:
            func_A7CF_b12(); break;
        case 0xA8BE:
            func_A8BE_b12(); break;
        case 0xA708:
            func_A708_b12(); break;
        case 0xDEA7:
            func_DEA7(); break;
        case 0xCB17:
            func_CB17(); break;
        case 0xC28D:
            func_C28D(); break;
        case 0xCB47:
            func_CB47(); break;
        case 0xE0CA:
            func_E0CA(); break;
        case 0xBA5B:
            switch (g_current_bank) {
                case 0: func_BA5B_b0(); break;
                case 1: func_BA5B_b1(); break;
                case 2: func_BA5B_b2(); break;
                case 3: func_BA5B_b3(); break;
                case 4: func_BA5B_b4(); break;
                case 5: func_BA5B_b5(); break;
                case 6: func_BA5B_b6(); break;
                case 7: func_BA5B_b7(); break;
                case 8: func_BA5B_b8(); break;
                case 9: func_BA5B_b9(); break;
                case 10: func_BA5B_b10(); break;
                case 11: func_BA5B_b11(); break;
                case 12: func_BA5B_b12(); break;
                case 13: func_BA5B_b13(); break;
                case 14: func_BA5B_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xC478:
            func_C478(); break;
        case 0xC88F:
            func_C88F(); break;
        case 0xDFC5:
            func_DFC5(); break;
        case 0xE016:
            func_E016(); break;
        case 0xEF4B:
            func_EF4B(); break;
        case 0xE02B:
            func_E02B(); break;
        case 0xD8EC:
            func_D8EC(); break;
        case 0xC130:
            func_C130(); break;
        case 0xC1B4:
            func_C1B4(); break;
        case 0xDD0F:
            func_DD0F(); break;
        case 0xE048:
            func_E048(); break;
        case 0xD2E7:
            func_D2E7(); break;
        case 0x823A:
            switch (g_current_bank) {
                case 5: func_823A_b5(); break;
                case 11: func_823A_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8132:
            func_8132_b5(); break;
        case 0x8EF1:
            switch (g_current_bank) {
                case 12: func_8EF1_b12(); break;
                case 14: func_8EF1_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8E6B:
            func_8E6B_b12(); break;
        case 0x9056:
            func_9056_b12(); break;
        case 0x9002:
            func_9002_b12(); break;
        case 0x8D5A:
            switch (g_current_bank) {
                case 12: func_8D5A_b12(); break;
                case 3: func_8D5A_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xF804:
            func_F804(); break;
        case 0x8E9B:
            func_8E9B_b12(); break;
        case 0x8BED:
            switch (g_current_bank) {
                case 12: func_8BED_b12(); break;
                case 7: func_8BED_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C04:
            func_8C04_b12(); break;
        case 0x8CF7:
            func_8CF7_b12(); break;
        case 0x8CA9:
            func_8CA9_b12(); break;
        case 0xF78B:
            func_F78B(); break;
        case 0x8B71:
            switch (g_current_bank) {
                case 12: func_8B71_b12(); break;
                case 11: func_8B71_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xF93C:
            func_F93C(); break;
        case 0xA88B:
            func_A88B_b14(); break;
        case 0xF2E3:
            func_F2E3(); break;
        case 0xCB9A:
            func_CB9A(); break;
        case 0xD062:
            func_D062(); break;
        case 0xF316:
            func_F316(); break;
        case 0x8201:
            switch (g_current_bank) {
                case 12: func_8201_b12(); break;
                case 8: func_8201_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x81C0:
            func_81C0_b12(); break;
        case 0x9910:
            func_9910_b12(); break;
        case 0x86BD:
            func_86BD_b14(); break;
        case 0x86A7:
            func_86A7_b14(); break;
        case 0xE87C:
            func_E87C(); break;
        case 0xF175:
            func_F175(); break;
        case 0xCFD0:
            func_CFD0(); break;
        case 0xFA47:
            func_FA47(); break;
        case 0xB92C:
            func_B92C_b0(); break;
        case 0xB931:
            func_B931_b4(); break;
        case 0xE8FF:
            func_E8FF(); break;
        case 0xB9ED:
            switch (g_current_bank) {
                case 14: func_B9ED_b14(); break;
                case 0: func_B9ED_b0(); break;
                case 1: func_B9ED_b1(); break;
                case 2: func_B9ED_b2(); break;
                case 3: func_B9ED_b3(); break;
                case 4: func_B9ED_b4(); break;
                case 5: func_B9ED_b5(); break;
                case 6: func_B9ED_b6(); break;
                case 7: func_B9ED_b7(); break;
                case 8: func_B9ED_b8(); break;
                case 9: func_B9ED_b9(); break;
                case 10: func_B9ED_b10(); break;
                case 11: func_B9ED_b11(); break;
                case 12: func_B9ED_b12(); break;
                case 13: func_B9ED_b13(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xF039:
            func_F039(); break;
        case 0xEC21:
            func_EC21(); break;
        case 0xEC51:
            func_EC51(); break;
        case 0xECAC:
            func_ECAC(); break;
        case 0xEC58:
            func_EC58(); break;
        case 0xB7D5:
            func_B7D5_b14(); break;
        case 0xBA4B:
            func_BA4B_b14(); break;
        case 0xB880:
            switch (g_current_bank) {
                case 14: func_B880_b14(); break;
                case 0: func_B880_b0(); break;
                case 1: func_B880_b1(); break;
                case 2: func_B880_b2(); break;
                case 3: func_B880_b3(); break;
                case 4: func_B880_b4(); break;
                case 5: func_B880_b5(); break;
                case 6: func_B880_b6(); break;
                case 7: func_B880_b7(); break;
                case 8: func_B880_b8(); break;
                case 9: func_B880_b9(); break;
                case 10: func_B880_b10(); break;
                case 11: func_B880_b11(); break;
                case 12: func_B880_b12(); break;
                case 13: func_B880_b13(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8058:
            func_8058_b2(); break;
        case 0x804C:
            switch (g_current_bank) {
                case 15: func_C04C(); break;
                case 6: func_804C_b6(); break;
                case 7: func_804C_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xD6A6:
            func_D6A6(); break;
        case 0xC6A6:
            func_C6A6(); break;
        case 0xDE60:
            func_DE60(); break;
        case 0x800A:
            switch (g_current_bank) {
                case 15: func_C00A(); break;
                case 7: func_800A_b7(); break;
                case 14: func_800A_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xE040:
            func_E040(); break;
        case 0xE9B8:
            func_E9B8(); break;
        case 0xC0E0:
            func_C0E0(); break;
        case 0xC0C0:
            func_C0C0(); break;
        case 0x8030:
            func_8030_b12(); break;
        case 0xD8AC:
            func_D8AC(); break;
        case 0xD7FF:
            func_D7FF(); break;
        case 0xD816:
            func_D816(); break;
        case 0xD82D:
            func_D82D(); break;
        case 0xD09B:
            func_D09B(); break;
        case 0xF3DC:
            func_F3DC(); break;
        case 0x92CA:
            func_92CA_b12(); break;
        case 0x94C8:
            func_94C8_b12(); break;
        case 0x954F:
            func_954F_b12(); break;
        case 0x9426:
            func_9426_b12(); break;
        case 0x98A7:
            switch (g_current_bank) {
                case 15: func_D8A7(); break;
                case 12: func_98A7_b12(); break;
                case 14: func_98A7_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x988F:
            func_988F_b12(); break;
        case 0x98E9:
            func_98E9_b12(); break;
        case 0x96B0:
            func_96B0_b12(); break;
        case 0x96C2:
            func_96C2_b12(); break;
        case 0xF842:
            func_F842(); break;
        case 0x92DB:
            func_92DB_b12(); break;
        case 0x93B4:
            func_93B4_b12(); break;
        case 0xDE06:
            func_DE06(); break;
        case 0xA872:
            switch (g_current_bank) {
                case 12: func_A872_b12(); break;
                case 0: func_A872_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA898:
            func_A898_b12(); break;
        case 0xA90F:
            func_A90F_b12(); break;
        case 0xAA94:
            func_AA94_b12(); break;
        case 0xCC15:
            func_CC15(); break;
        case 0xDC78:
            func_DC78(); break;
        case 0xCCE7:
            func_CCE7(); break;
        case 0xCEB8:
            func_CEB8(); break;
        case 0xDD46:
            func_DD46(); break;
        case 0xE103:
            func_E103(); break;
        case 0xE2C8:
            func_E2C8(); break;
        case 0xE174:
            func_E174(); break;
        case 0xE0E8:
            func_E0E8(); break;
        case 0xE0C9:
            func_E0C9(); break;
        case 0xE526:
            func_E526(); break;
        case 0xE905:
            func_E905(); break;
        case 0xE95D:
            func_E95D(); break;
        case 0xE9C0:
            func_E9C0(); break;
        case 0xECF6:
            func_ECF6(); break;
        case 0xC0C3:
            func_C0C3(); break;
        case 0xBA92:
            func_BA92_b14(); break;
        case 0xBAD9:
            func_BAD9_b14(); break;
        case 0xC5EB:
            func_C5EB(); break;
        case 0xC59D:
            func_C59D(); break;
        case 0xC89B:
            func_C89B(); break;
        case 0xC8B4:
            func_C8B4(); break;
        case 0xE02A:
            func_E02A(); break;
        case 0xCA2E:
            func_CA2E(); break;
        case 0xB7BF:
            switch (g_current_bank) {
                case 0: func_B7BF_b0(); break;
                case 1: func_B7BF_b1(); break;
                case 2: func_B7BF_b2(); break;
                case 3: func_B7BF_b3(); break;
                case 4: func_B7BF_b4(); break;
                case 5: func_B7BF_b5(); break;
                case 6: func_B7BF_b6(); break;
                case 7: func_B7BF_b7(); break;
                case 8: func_B7BF_b8(); break;
                case 9: func_B7BF_b9(); break;
                case 10: func_B7BF_b10(); break;
                case 11: func_B7BF_b11(); break;
                case 12: func_B7BF_b12(); break;
                case 13: func_B7BF_b13(); break;
                case 14: func_B7BF_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xED45:
            func_ED45(); break;
        case 0xDA42:
            func_DA42(); break;
        case 0xD9D6:
            func_D9D6(); break;
        case 0xDA2F:
            func_DA2F(); break;
        case 0xD941:
            func_D941(); break;
        case 0xD2CE:
            func_D2CE(); break;
        case 0xE06A:
            func_E06A(); break;
        case 0xD2A6:
            func_D2A6(); break;
        case 0xD2E6:
            func_D2E6(); break;
        case 0xD29F:
            func_D29F(); break;
        case 0xD3A6:
            func_D3A6(); break;
        case 0xD4DC:
            func_D4DC(); break;
        case 0xD4F0:
            func_D4F0(); break;
        case 0x82FF:
            func_82FF_b5(); break;
        case 0x8544:
            switch (g_current_bank) {
                case 5: func_8544_b5(); break;
                case 12: func_8544_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x82E3:
            switch (g_current_bank) {
                case 5: func_82E3_b5(); break;
                case 6: func_82E3_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x83AD:
            func_83AD_b5(); break;
        case 0x83CD:
            func_83CD_b5(); break;
        case 0x83B7:
            func_83B7_b5(); break;
        case 0x83FB:
            func_83FB_b5(); break;
        case 0x8495:
            func_8495_b5(); break;
        case 0xF000:
            func_F000(); break;
        case 0xB286:
            func_B286_b5(); break;
        case 0x8ED1:
            func_8ED1_b5(); break;
        case 0xA93C:
            func_A93C_b5(); break;
        case 0x891F:
            func_891F_b5(); break;
        case 0x892E:
            func_892E_b5(); break;
        case 0x8EED:
            func_8EED_b5(); break;
        case 0x81F1:
            func_81F1_b5(); break;
        case 0x820D:
            func_820D_b5(); break;
        case 0xF832:
            func_F832(); break;
        case 0xF839:
            func_F839(); break;
        case 0xF826:
            func_F826(); break;
        case 0x8FF6:
            func_8FF6_b12(); break;
        case 0x880E:
            switch (g_current_bank) {
                case 12: func_880E_b12(); break;
                case 0: func_880E_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x87FE:
            func_87FE_b12(); break;
        case 0xF822:
            func_F822(); break;
        case 0xF828:
            func_F828(); break;
        case 0x87F0:
            func_87F0_b12(); break;
        case 0x87F7:
            switch (g_current_bank) {
                case 12: func_87F7_b12(); break;
                case 6: func_87F7_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8F51:
            func_8F51_b12(); break;
        case 0xF7B7:
            func_F7B7(); break;
        case 0xFA03:
            func_FA03(); break;
        case 0x8C58:
            func_8C58_b12(); break;
        case 0x8C36:
            switch (g_current_bank) {
                case 12: func_8C36_b12(); break;
                case 0: func_8C36_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8EB3:
            func_8EB3_b12(); break;
        case 0xF785:
            func_F785(); break;
        case 0x9A6A:
            func_9A6A_b12(); break;
        case 0x9AF7:
            func_9AF7_b12(); break;
        case 0xEDEC:
            func_EDEC(); break;
        case 0xEE05:
            func_EE05(); break;
        case 0xEE0D:
            func_EE0D(); break;
        case 0x8CF3:
            func_8CF3_b12(); break;
        case 0xFC0B:
            func_FC0B(); break;
        case 0xF30F:
            func_F30F(); break;
        case 0xF44A:
            func_F44A(); break;
        case 0xF5D9:
            func_F5D9(); break;
        case 0x86B5:
            func_86B5_b14(); break;
        case 0xE8C6:
            func_E8C6(); break;
        case 0xFA55:
            func_FA55(); break;
        case 0xD127:
            func_D127(); break;
        case 0xBA48:
            func_BA48_b14(); break;
        case 0xF072:
            func_F072(); break;
        case 0xB9C8:
            switch (g_current_bank) {
                case 6: func_B9C8_b6(); break;
                case 3: func_B9C8_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xD6A5:
            func_D6A5(); break;
        case 0xDD4E:
            func_DD4E(); break;
        case 0xE036:
            func_E036(); break;
        case 0x92ED:
            func_92ED_b12(); break;
        case 0x948A:
            func_948A_b12(); break;
        case 0x9349:
            func_9349_b12(); break;
        case 0x9539:
            func_9539_b12(); break;
        case 0x9545:
            func_9545_b12(); break;
        case 0x93B1:
            func_93B1_b12(); break;
        case 0xDD13:
            func_DD13(); break;
        case 0xCF2B:
            func_CF2B(); break;
        case 0xE752:
            func_E752(); break;
        case 0xE2F4:
            func_E2F4(); break;
        case 0xE399:
            func_E399(); break;
        case 0xE6C8:
            func_E6C8(); break;
        case 0xE32B:
            func_E32B(); break;
        case 0xE627:
            func_E627(); break;
        case 0xE8E9:
            func_E8E9(); break;
        case 0xE379:
            func_E379(); break;
        case 0xE14F:
            func_E14F(); break;
        case 0xE153:
            func_E153(); break;
        case 0xE220:
            func_E220(); break;
        case 0xE27F:
            func_E27F(); break;
        case 0xE291:
            func_E291(); break;
        case 0xE21A:
            func_E21A(); break;
        case 0xE7C5:
            func_E7C5(); break;
        case 0xEB2F:
            func_EB2F(); break;
        case 0xDAA0:
            func_DAA0(); break;
        case 0xEA50:
            func_EA50(); break;
        case 0xDADC:
            func_DADC(); break;
        case 0xD6CE:
            func_D6CE(); break;
        case 0xD6F5:
            func_D6F5(); break;
        case 0xEA13:
            func_EA13(); break;
        case 0xDABE:
            func_DABE(); break;
        case 0xDACD:
            func_DACD(); break;
        case 0xED72:
            func_ED72(); break;
        case 0xEEA9:
            func_EEA9(); break;
        case 0xED9D:
            func_ED9D(); break;
        case 0xEEBF:
            func_EEBF(); break;
        case 0xEDCD:
            func_EDCD(); break;
        case 0xEE93:
            func_EE93(); break;
        case 0xD0AD:
            func_D0AD(); break;
        case 0xE052:
            func_E052(); break;
        case 0xD393:
            func_D393(); break;
        case 0xD276:
            func_D276(); break;
        case 0xD38E:
            func_D38E(); break;
        case 0xD445:
            func_D445(); break;
        case 0xD4D7:
            func_D4D7(); break;
        case 0xEFFA:
            func_EFFA(); break;
        case 0xA935:
            func_A935_b5(); break;
        case 0xF791:
            func_F791(); break;
        case 0xFC18:
            func_FC18(); break;
        case 0x9AED:
            func_9AED_b12(); break;
        case 0xFBF0:
            func_FBF0(); break;
        case 0xF81E:
            func_F81E(); break;
        case 0xF84A:
            func_F84A(); break;
        case 0xD1F6:
            func_D1F6(); break;
        case 0xB81D:
            func_B81D_b6(); break;
        case 0xBCB8:
            func_BCB8_b6(); break;
        case 0xFF00:
            func_FF00(); break;
        case 0x9544:
            func_9544_b12(); break;
        case 0x9541:
            func_9541_b12(); break;
        case 0xED12:
            func_ED12(); break;
        case 0xD0F6:
            func_D0F6(); break;
        case 0xF8EB:
            func_F8EB(); break;
        case 0xC000:
            func_C000(); break;
        case 0xE8B2:
            func_E8B2(); break;
        case 0xE43A:
            func_E43A(); break;
        case 0xE4F6:
            func_E4F6(); break;
        case 0xE444:
            func_E444(); break;
        case 0xE3FC:
            func_E3FC(); break;
        case 0xE42C:
            func_E42C(); break;
        case 0xE49A:
            func_E49A(); break;
        case 0xE4C9:
            func_E4C9(); break;
        case 0xE691:
            func_E691(); break;
        case 0xE65B:
            func_E65B(); break;
        case 0xE87F:
            func_E87F(); break;
        case 0xE16B:
            func_E16B(); break;
        case 0xE288:
            func_E288(); break;
        case 0xE5DA:
            func_E5DA(); break;
        case 0xE866:
            func_E866(); break;
        case 0xE815:
            func_E815(); break;
        case 0xDEF5:
            func_DEF5(); break;
        case 0xD76E:
            func_D76E(); break;
        case 0xDE66:
            func_DE66(); break;
        case 0xDF64:
            func_DF64(); break;
        case 0xEE15:
            func_EE15(); break;
        case 0xEED2:
            func_EED2(); break;
        case 0xEE3F:
            func_EE3F(); break;
        case 0xEE69:
            func_EE69(); break;
        case 0xD3BA:
            func_D3BA(); break;
        case 0xD503:
            func_D503(); break;
        case 0xF7F6:
            func_F7F6(); break;
        case 0xD1EB:
            func_D1EB(); break;
        case 0xD258:
            func_D258(); break;
        case 0xD244:
            func_D244(); break;
        case 0xFBAF:
            func_FBAF(); break;
        case 0xE433:
            func_E433(); break;
        case 0xE439:
            func_E439(); break;
        case 0xE664:
            func_E664(); break;
        case 0xE62D:
            func_E62D(); break;
        case 0xD210:
            func_D210(); break;
        case 0xC0A9:
            func_C0A9(); break;
        case 0xC0AA:
            func_C0AA(); break;
        case 0xC01B:
            func_C01B(); break;
        case 0xC01C:
            func_C01C(); break;
        case 0xCA20:
            func_CA20(); break;
        case 0xCA21:
            func_CA21(); break;
        case 0xD0CA:
            func_D0CA(); break;
        case 0xD0CB:
            func_D0CB(); break;
        case 0xFAD0:
            func_FAD0(); break;
        case 0xFAD1:
            func_FAD1(); break;
        case 0xC059:
            func_C059(); break;
        case 0xE885:
            func_E885(); break;
        case 0xE886:
            func_E886(); break;
        case 0xC8E8:
            func_C8E8(); break;
        case 0xC8E9:
            func_C8E9(); break;
        case 0xE985:
            func_E985(); break;
        case 0xE986:
            func_E986(); break;
        case 0xC8EA:
            func_C8EA(); break;
        case 0xDC20:
            func_DC20(); break;
        case 0xCFDD:
            func_CFDD(); break;
        case 0xE805:
            func_E805(); break;
        case 0xE806:
            func_E806(); break;
        case 0xC6C8:
            func_C6C8(); break;
        case 0xC6C9:
            func_C6C9(); break;
        case 0xF5D1:
            func_F5D1(); break;
        case 0xF991:
            func_F991(); break;
        case 0xE721:
            func_E721(); break;
        case 0xF9E8:
            func_F9E8(); break;
        case 0xF976:
            func_F976(); break;
        case 0xC0BE:
            func_C0BE(); break;
        case 0xFA86:
            func_FA86(); break;
        case 0xFB4C:
            func_FB4C(); break;
        case 0xC904:
            func_C904(); break;
        case 0xC905:
            func_C905(); break;
        case 0xFA76:
            func_FA76(); break;
        case 0xED38:
            func_ED38(); break;
        case 0xED39:
            func_ED39(); break;
        case 0xED04:
            func_ED04(); break;
        case 0xF008:
            func_F008(); break;
        case 0xF009:
            func_F009(); break;
        case 0xCA4C:
            func_CA4C(); break;
        case 0xC4CB:
            func_C4CB(); break;
        case 0xC0AE:
            func_C0AE(); break;
        case 0xC0AF:
            func_C0AF(); break;
        case 0xC903:
            func_C903(); break;
        case 0xC18D:
            func_C18D(); break;
        case 0xC18E:
            func_C18E(); break;
        case 0xC02E:
            func_C02E(); break;
        case 0xC12E:
            func_C12E(); break;
        case 0xC12F:
            func_C12F(); break;
        case 0xCD04:
            func_CD04(); break;
        case 0xCD05:
            func_CD05(); break;
        case 0xC1AE:
            func_C1AE(); break;
        case 0xCA04:
            func_CA04(); break;
        case 0xCA05:
            func_CA05(); break;
        case 0xD1D0:
            func_D1D0(); break;
        case 0xCC9D:
            func_CC9D(); break;
        case 0xD49D:
            func_D49D(); break;
        case 0xD49E:
            func_D49E(); break;
        case 0xCA02:
            func_CA02(); break;
        case 0xED10:
            func_ED10(); break;
        case 0xED11:
            func_ED11(); break;
        case 0xCD70:
            func_CD70(); break;
        case 0xC78D:
            func_C78D(); break;
        case 0xC78E:
            func_C78E(); break;
        case 0xC902:
            func_C902(); break;
        case 0xF0FF:
            func_F0FF(); break;
        case 0xF100:
            func_F100(); break;
        case 0xCA85:
            func_CA85(); break;
        case 0xCA86:
            func_CA86(); break;
        case 0xC8CA:
            func_C8CA(); break;
        case 0xCB85:
            func_CB85(); break;
        case 0xCAB2:
            func_CAB2(); break;
        case 0xC9CA:
            func_C9CA(); break;
        case 0xC9CB:
            func_C9CB(); break;
        case 0xD0FF:
            func_D0FF(); break;
        case 0xD100:
            func_D100(); break;
        case 0xC811:
            func_C811(); break;
        case 0xCA65:
            func_CA65(); break;
        case 0xCA66:
            func_CA66(); break;
        case 0xCC86:
            func_CC86(); break;
        case 0xCBA5:
            func_CBA5(); break;
        case 0xCD85:
            func_CD85(); break;
        case 0xC19A:
            func_C19A(); break;
        case 0xC8C2:
            func_C8C2(); break;
        case 0xC8C8:
            func_C8C8(); break;
        case 0xD0C9:
            func_D0C9(); break;
        case 0xE6D1:
            func_E6D1(); break;
        case 0xCCB1:
            func_CCB1(); break;
        case 0xCCB2:
            func_CCB2(); break;
        case 0xC9CC:
            func_C9CC(); break;
        case 0xC9CD:
            func_C9CD(); break;
        case 0xC80F:
            func_C80F(); break;
        case 0xD081:
            func_D081(); break;
        case 0xEBD0:
            func_EBD0(); break;
        case 0xEBD1:
            func_EBD1(); break;
        case 0xC8EB:
            func_C8EB(); break;
        case 0xC8EC:
            func_C8EC(); break;
        case 0xC860:
            func_C860(); break;
        case 0xC861:
            func_C861(); break;
        case 0xE9D0:
            func_E9D0(); break;
        case 0xCC1B:
            func_CC1B(); break;
        case 0xC155:
            func_C155(); break;
        case 0xC803:
            func_C803(); break;
        case 0xC804:
            func_C804(); break;
        case 0xF029:
            func_F029(); break;
        case 0xF02A:
            func_F02A(); break;
        case 0xCAA5:
            func_CAA5(); break;
        case 0xCAA6:
            func_CAA6(); break;
        case 0xC54C:
            func_C54C(); break;
        case 0xC1C6:
            func_C1C6(); break;
        case 0xF3D7:
            func_F3D7(); break;
        case 0xCCBD:
            func_CCBD(); break;
        case 0xCCBE:
            func_CCBE(); break;
        case 0xE49E:
            func_E49E(); break;
        case 0xDC9D:
            func_DC9D(); break;
        case 0xDC9E:
            func_DC9E(); break;
        case 0xC296:
            func_C296(); break;
        case 0xDFB9:
            func_DFB9(); break;
        case 0xDFBA:
            func_DFBA(); break;
        case 0xC25C:
            func_C25C(); break;
        case 0xCCE6:
            func_CCE6(); break;
        case 0xD0CC:
            func_D0CC(); break;
        case 0xD0CD:
            func_D0CD(); break;
        case 0xC802:
            func_C802(); break;
        case 0xC259:
            func_C259(); break;
        case 0xC27D:
            func_C27D(); break;
        case 0xCDB6:
            func_CDB6(); break;
        case 0xD030:
            func_D030(); break;
        case 0xD031:
            func_D031(); break;
        case 0xC2B5:
            func_C2B5(); break;
        case 0xC2B6:
            func_C2B6(); break;
        case 0xC9C3:
            func_C9C3(); break;
        case 0xF0C9:
            func_F0C9(); break;
        case 0xF44C:
            func_F44C(); break;
        case 0xF44D:
            func_F44D(); break;
        case 0xCFF5:
            func_CFF5(); break;
        case 0xC316:
            func_C316(); break;
        case 0xE86D:
            func_E86D(); break;
        case 0xC321:
            func_C321(); break;
        case 0xE8C4:
            func_E8C4(); break;
        case 0xC9E8:
            func_C9E8(); break;
        case 0xC9E9:
            func_C9E9(); break;
        case 0xF004:
            func_F004(); break;
        case 0xF005:
            func_F005(); break;
        case 0xC908:
            func_C908(); break;
        case 0xC909:
            func_C909(); break;
        case 0xF00D:
            func_F00D(); break;
        case 0xF00E:
            func_F00E(); break;
        case 0xD009:
            func_D009(); break;
        case 0xD00A:
            func_D00A(); break;
        case 0xD004:
            func_D004(); break;
        case 0xD005:
            func_D005(); break;
        case 0xC912:
            func_C912(); break;
        case 0xF040:
            func_F040(); break;
        case 0xF0B8:
            func_F0B8(); break;
        case 0xF0B9:
            func_F0B9(); break;
        case 0xC90B:
            func_C90B(); break;
        case 0xC90C:
            func_C90C(); break;
        case 0xC37B:
            func_C37B(); break;
        case 0xC387:
            func_C387(); break;
        case 0xC388:
            func_C388(); break;
        case 0xF058:
            func_F058(); break;
        case 0xC394:
            func_C394(); break;
        case 0xD002:
            func_D002(); break;
        case 0xE538:
            func_E538(); break;
        case 0xE539:
            func_E539(); break;
        case 0xC46D:
            func_C46D(); break;
        case 0xE600:
            func_E600(); break;
        case 0xC474:
            func_C474(); break;
        case 0xCAAA:
            func_CAAA(); break;
        case 0xCAAB:
            func_CAAB(); break;
        case 0xC710:
            func_C710(); break;
        case 0xC0A8:
            func_C0A8(); break;
        case 0xC49E:
            func_C49E(); break;
        case 0xC49B:
            func_C49B(); break;
        case 0xC49C:
            func_C49C(); break;
        case 0xC615:
            func_C615(); break;
        case 0xC616:
            func_C616(); break;
        case 0xC7C5:
            func_C7C5(); break;
        case 0xC5C7:
            func_C5C7(); break;
        case 0xC5C8:
            func_C5C8(); break;
        case 0xC578:
            func_C578(); break;
        case 0xC579:
            func_C579(); break;
        case 0xC532:
            func_C532(); break;
        case 0xC533:
            func_C533(); break;
        case 0xF729:
            func_F729(); break;
        case 0xF72A:
            func_F72A(); break;
        case 0xF85A:
            func_F85A(); break;
        case 0xE420:
            func_E420(); break;
        case 0xE421:
            func_E421(); break;
        case 0xD0E5:
            func_D0E5(); break;
        case 0xC07C:
            func_C07C(); break;
        case 0xDC47:
            func_DC47(); break;
        case 0xCA26:
            func_CA26(); break;
        case 0xD490:
            func_D490(); break;
        case 0xD491:
            func_D491(); break;
        case 0xD920:
            func_D920(); break;
        case 0xD921:
            func_D921(); break;
        case 0xC0DA:
            func_C0DA(); break;
        case 0xC4C0:
            func_C4C0(); break;
        case 0xCDD0:
            func_CDD0(); break;
        case 0xCDD1:
            func_CDD1(); break;
        case 0xC599:
            func_C599(); break;
        case 0xC59A:
            func_C59A(); break;
        case 0xD03F:
            func_D03F(); break;
        case 0xD040:
            func_D040(); break;
        case 0xCE1A:
            func_CE1A(); break;
        case 0xCE12:
            func_CE12(); break;
        case 0xCE13:
            func_CE13(); break;
        case 0xD1AD:
            func_D1AD(); break;
        case 0xD1AE:
            func_D1AE(); break;
        case 0xEC8D:
            func_EC8D(); break;
        case 0xEC8E:
            func_EC8E(); break;
        case 0xED8D:
            func_ED8D(); break;
        case 0xED8E:
            func_ED8E(); break;
        case 0xF958:
            func_F958(); break;
        case 0xC68E:
            func_C68E(); break;
        case 0xC9C6:
            func_C9C6(); break;
        case 0xC9C7:
            func_C9C7(); break;
        case 0xD906:
            func_D906(); break;
        case 0xD907:
            func_D907(); break;
        case 0xC68F:
            func_C68F(); break;
        case 0xC690:
            func_C690(); break;
        case 0xF0C7:
            func_F0C7(); break;
        case 0xC520:
            func_C520(); break;
        case 0xC521:
            func_C521(); break;
        case 0xD7C6:
            func_D7C6(); break;
        case 0xC9AD:
            func_C9AD(); break;
        case 0xC8A9:
            func_C8A9(); break;
        case 0xC659:
            func_C659(); break;
        case 0xCD4C:
            func_CD4C(); break;
        case 0xCD4D:
            func_CD4D(); break;
        case 0xC8CE:
            func_C8CE(); break;
        case 0xC2AE:
            func_C2AE(); break;
        case 0xC2AF:
            func_C2AF(); break;
        case 0xE003:
            func_E003(); break;
        case 0xE004:
            func_E004(); break;
        case 0xE803:
            func_E803(); break;
        case 0xE804:
            func_E804(); break;
        case 0xC38F:
            func_C38F(); break;
        case 0xC4AE:
            func_C4AE(); break;
        case 0xC4AF:
            func_C4AF(); break;
        case 0xC48E:
            func_C48E(); break;
        case 0xC48F:
            func_C48F(); break;
        case 0xC3AE:
            func_C3AE(); break;
        case 0xC3AF:
            func_C3AF(); break;
        case 0xC28E:
            func_C28E(); break;
        case 0xC9C8:
            func_C9C8(); break;
        case 0xC9C9:
            func_C9C9(); break;
        case 0xF050:
            func_F050(); break;
        case 0xEAF0:
            func_EAF0(); break;
        case 0xEAF1:
            func_EAF1(); break;
        case 0xC9EA:
            func_C9EA(); break;
        case 0xC9EB:
            func_C9EB(); break;
        case 0xD057:
            func_D057(); break;
        case 0xD058:
            func_D058(); break;
        case 0xD059:
            func_D059(); break;
        case 0xEA4D:
            func_EA4D(); break;
        case 0xF059:
            func_F059(); break;
        case 0xF05A:
            func_F05A(); break;
        case 0xC991:
            func_C991(); break;
        case 0xF05B:
            func_F05B(); break;
        case 0xC9AC:
            func_C9AC(); break;
        case 0xF05C:
            func_F05C(); break;
        case 0xC8F0:
            func_C8F0(); break;
        case 0xC8F1:
            func_C8F1(); break;
        case 0xD055:
            func_D055(); break;
        case 0xD056:
            func_D056(); break;
        case 0xD84C:
            func_D84C(); break;
        case 0xD84D:
            func_D84D(); break;
        case 0xD05C:
            func_D05C(); break;
        case 0xD05D:
            func_D05D(); break;
        case 0xD04C:
            func_D04C(); break;
        case 0xD04D:
            func_D04D(); break;
        case 0xC6D1:
            func_C6D1(); break;
        case 0xC6BF:
            func_C6BF(); break;
        case 0xD05E:
            func_D05E(); break;
        case 0xC83D:
            func_C83D(); break;
        case 0xF060:
            func_F060(); break;
        case 0xC927:
            func_C927(); break;
        case 0xD060:
            func_D060(); break;
        case 0xC87B:
            func_C87B(); break;
        case 0xE938:
            func_E938(); break;
        case 0xE939:
            func_E939(); break;
        case 0xF0A8:
            func_F0A8(); break;
        case 0xF088:
            func_F088(); break;
        case 0xF089:
            func_F089(); break;
        case 0xD088:
            func_D088(); break;
        case 0xC865:
            func_C865(); break;
        case 0xCD20:
            func_CD20(); break;
        case 0xCD21:
            func_CD21(); break;
        case 0xC5EC:
            func_C5EC(); break;
        case 0xC59E:
            func_C59E(); break;
        case 0xC89C:
            func_C89C(); break;
        case 0xCE0D:
            func_CE0D(); break;
        case 0xCE0E:
            func_CE0E(); break;
        case 0xC6AE:
            func_C6AE(); break;
        case 0xE98D:
            func_E98D(); break;
        case 0xE98E:
            func_E98E(); break;
        case 0xE88D:
            func_E88D(); break;
        case 0xE8AD:
            func_E8AD(); break;
        case 0xE8AE:
            func_E8AE(); break;
        case 0xE9AD:
            func_E9AD(); break;
        case 0xE9AE:
            func_E9AE(); break;
        case 0xD6D0:
            func_D6D0(); break;
        case 0xD6D1:
            func_D6D1(); break;
        case 0xD878:
            func_D878(); break;
        case 0xFB11:
            func_FB11(); break;
        case 0xE000:
            func_E000(); break;
        case 0xE001:
            func_E001(); break;
        case 0xE808:
            func_E808(); break;
        case 0xD0E8:
            func_D0E8(); break;
        case 0xD0E9:
            func_D0E9(); break;
        case 0xE5D1:
            func_E5D1(); break;
        case 0xCBC0:
            func_CBC0(); break;
        case 0xCA79:
            func_CA79(); break;
        case 0xF01B:
            func_F01B(); break;
        case 0xF01C:
            func_F01C(); break;
        case 0xD620:
            func_D620(); break;
        case 0xD621:
            func_D621(); break;
        case 0xC9D7:
            func_C9D7(); break;
        case 0xE6C9:
            func_E6C9(); break;
        case 0xE6CA:
            func_E6CA(); break;
        case 0xC9D1:
            func_C9D1(); break;
        case 0xE014:
            func_E014(); break;
        case 0xF014:
            func_F014(); break;
        case 0xE7F0:
            func_E7F0(); break;
        case 0xE7F1:
            func_E7F1(); break;
        case 0xD010:
            func_D010(); break;
        case 0xE6B8:
            func_E6B8(); break;
        case 0xCA36:
            func_CA36(); break;
        case 0xE6CB:
            func_E6CB(); break;
        case 0xE629:
            func_E629(); break;
        case 0xE62A:
            func_E62A(); break;
        case 0xFA4C:
            func_FA4C(); break;
        case 0xFA4D:
            func_FA4D(); break;
        case 0xC9FB:
            func_C9FB(); break;
        case 0xFB71:
            func_FB71(); break;
        case 0xFB51:
            func_FB51(); break;
        case 0xCAA1:
            func_CAA1(); break;
        case 0xF010:
            func_F010(); break;
        case 0xC51A:
            func_C51A(); break;
        case 0xC51B:
            func_C51B(); break;
        case 0xF01A:
            func_F01A(); break;
        case 0xCA16:
            func_CA16(); break;
        case 0xCA17:
            func_CA17(); break;
        case 0xF1D0:
            func_F1D0(); break;
        case 0xF1D1:
            func_F1D1(); break;
        case 0xCA18:
            func_CA18(); break;
        case 0xDAA6:
            func_DAA6(); break;
        case 0xDAE6:
            func_DAE6(); break;
        case 0xDAE7:
            func_DAE7(); break;
        case 0xCABD:
            func_CABD(); break;
        case 0xCB30:
            func_CB30(); break;
        case 0xCAB6:
            func_CAB6(); break;
        case 0xED21:
            func_ED21(); break;
        case 0xC0A3:
            func_C0A3(); break;
        case 0xF7D0:
            func_F7D0(); break;
        case 0xF7D1:
            func_F7D1(); break;
        case 0xD01F:
            func_D01F(); break;
        case 0xD020:
            func_D020(); break;
        case 0xC914:
            func_C914(); break;
        case 0xC915:
            func_C915(); break;
        case 0xFA90:
            func_FA90(); break;
        case 0xFA91:
            func_FA91(); break;
        case 0xFB31:
            func_FB31(); break;
        case 0xCB48:
            func_CB48(); break;
        case 0xCB3F:
            func_CB3F(); break;
        case 0xCB40:
            func_CB40(); break;
        case 0xE61B:
            func_E61B(); break;
        case 0xE61C:
            func_E61C(); break;
        case 0xCB97:
            func_CB97(); break;
        case 0xCB98:
            func_CB98(); break;
        case 0xCB99:
            func_CB99(); break;
        case 0xF0AA:
            func_F0AA(); break;
        case 0xC807:
            func_C807(); break;
        case 0xC808:
            func_C808(); break;
        case 0xEED0:
            func_EED0(); break;
        case 0xD021:
            func_D021(); break;
        case 0xF002:
            func_F002(); break;
        case 0xCC1E:
            func_CC1E(); break;
        case 0xC6CC:
            func_C6CC(); break;
        case 0xC6CD:
            func_C6CD(); break;
        case 0xF012:
            func_F012(); break;
        case 0xE647:
            func_E647(); break;
        case 0xCD33:
            func_CD33(); break;
        case 0xC621:
            func_C621(); break;
        case 0xD007:
            func_D007(); break;
        case 0xDBD0:
            func_DBD0(); break;
        case 0xDBD1:
            func_DBD1(); break;
        case 0xDFFE:
            func_DFFE(); break;
        case 0xF7DF:
            func_F7DF(); break;
        case 0xF7E0:
            func_F7E0(); break;
        case 0xEFBF:
            func_EFBF(); break;
        case 0xFB7F:
            func_FB7F(); break;
        case 0xE820:
            func_E820(); break;
        case 0xE821:
            func_E821(); break;
        case 0xE8D0:
            func_E8D0(); break;
        case 0xE8D1:
            func_E8D1(); break;
        case 0xE902:
            func_E902(); break;
        case 0xC897:
            func_C897(); break;
        case 0xCE1B:
            func_CE1B(); break;
        case 0xCE1C:
            func_CE1C(); break;
        case 0xCD79:
            func_CD79(); break;
        case 0xD09C:
            func_D09C(); break;
        case 0xC0C9:
            func_C0C9(); break;
        case 0xF590:
            func_F590(); break;
        case 0xF591:
            func_F591(); break;
        case 0xC699:
            func_C699(); break;
        case 0xC69A:
            func_C69A(); break;
        case 0xC820:
            func_C820(); break;
        case 0xE6F8:
            func_E6F8(); break;
        case 0xC603:
            func_C603(); break;
        case 0xC604:
            func_C604(); break;
        case 0xF2D0:
            func_F2D0(); break;
        case 0xCF07:
            func_CF07(); break;
        case 0xCF09:
            func_CF09(); break;
        case 0xCF2C:
            func_CF2C(); break;
        case 0xCF19:
            func_CF19(); break;
        case 0xCF1A:
            func_CF1A(); break;
        case 0xCF22:
            func_CF22(); break;
        case 0xCF23:
            func_CF23(); break;
        case 0xE909:
            func_E909(); break;
        case 0xE7B0:
            func_E7B0(); break;
        case 0xFB2A:
            func_FB2A(); break;
        case 0xC51F:
            func_C51F(); break;
        case 0xF020:
            func_F020(); break;
        case 0xC906:
            func_C906(); break;
        case 0xE60D:
            func_E60D(); break;
        case 0xE60E:
            func_E60E(); break;
        case 0xCFBD:
            func_CFBD(); break;
        case 0xCFBE:
            func_CFBE(); break;
        case 0xCFBC:
            func_CFBC(); break;
        case 0xD0A9:
            func_D0A9(); break;
        case 0xD0AA:
            func_D0AA(); break;
        case 0xC880:
            func_C880(); break;
        case 0xE8A8:
            func_E8A8(); break;
        case 0xE8A9:
            func_E8A9(); break;
        case 0xF6D0:
            func_F6D0(); break;
        case 0xF6D1:
            func_F6D1(); break;
        case 0xC61F:
            func_C61F(); break;
        case 0xF022:
            func_F022(); break;
        case 0xC088:
            func_C088(); break;
        case 0xC089:
            func_C089(); break;
        case 0xF9C0:
            func_F9C0(); break;
        case 0xF9C1:
            func_F9C1(); break;
        case 0xD015:
            func_D015(); break;
        case 0xD016:
            func_D016(); break;
        case 0xCFBA:
            func_CFBA(); break;
        case 0xCFBB:
            func_CFBB(); break;
        case 0xCD3B:
            func_CD3B(); break;
        case 0xCCEB:
            func_CCEB(); break;
        case 0xCCEC:
            func_CCEC(); break;
        case 0xCFCB:
            func_CFCB(); break;
        case 0xE9A5:
            func_E9A5(); break;
        case 0xE9A6:
            func_E9A6(); break;
        case 0xE8A5:
            func_E8A5(); break;
        case 0xE8A6:
            func_E8A6(); break;
        case 0xD03C:
            func_D03C(); break;
        case 0xD091:
            func_D091(); break;
        case 0xF0BA:
            func_F0BA(); break;
        case 0xD48E:
            func_D48E(); break;
        case 0xC069:
            func_C069(); break;
        case 0xF710:
            func_F710(); break;
        case 0xF711:
            func_F711(); break;
        case 0xE0FD:
            func_E0FD(); break;
        case 0xE0FE:
            func_E0FE(); break;
        case 0xD0E0:
            func_D0E0(); break;
        case 0xD0E1:
            func_D0E1(); break;
        case 0xF370:
            func_F370(); break;
        case 0xE80C:
            func_E80C(); break;
        case 0xE80D:
            func_E80D(); break;
        case 0xF610:
            func_F610(); break;
        case 0xC800:
            func_C800(); break;
        case 0xF690:
            func_F690(); break;
        case 0xF691:
            func_F691(); break;
        case 0xCC16:
            func_CC16(); break;
        case 0xF621:
            func_F621(); break;
        case 0xE699:
            func_E699(); break;
        case 0xE69A:
            func_E69A(); break;
        case 0xC8AA:
            func_C8AA(); break;
        case 0xC8AB:
            func_C8AB(); break;
        case 0xF090:
            func_F090(); break;
        case 0xF091:
            func_F091(); break;
        case 0xF69A:
            func_F69A(); break;
        case 0xF0A2:
            func_F0A2(); break;
        case 0xF0A3:
            func_F0A3(); break;
        case 0xD0BD:
            func_D0BD(); break;
        case 0xD0BE:
            func_D0BE(); break;
        case 0xCCE8:
            func_CCE8(); break;
        case 0xC954:
            func_C954(); break;
        case 0xE7BD:
            func_E7BD(); break;
        case 0xE7BE:
            func_E7BE(); break;
        case 0xD1E7:
            func_D1E7(); break;
        case 0xD1E8:
            func_D1E8(); break;
        case 0xE9BD:
            func_E9BD(); break;
        case 0xD1E9:
            func_D1E9(); break;
        case 0xD1EA:
            func_D1EA(); break;
        case 0xC961:
            func_C961(); break;
        case 0xF1F0:
            func_F1F0(); break;
        case 0xF1F1:
            func_F1F1(); break;
        case 0xE0AB:
            func_E0AB(); break;
        case 0xD274:
            func_D274(); break;
        case 0xD245:
            func_D245(); break;
        case 0xCA5C:
            func_CA5C(); break;
        case 0xCA5D:
            func_CA5D(); break;
        case 0xC3D0:
            func_C3D0(); break;
        case 0xC3D1:
            func_C3D1(); break;
        case 0xE609:
            func_E609(); break;
        case 0xE65F:
            func_E65F(); break;
        case 0xE660:
            func_E660(); break;
        case 0xEFF1:
            func_EFF1(); break;
        case 0xC805:
            func_C805(); break;
        case 0xE8C8:
            func_E8C8(); break;
        case 0xE8C9:
            func_E8C9(); break;
        case 0xEA11:
            func_EA11(); break;
        case 0xD277:
            func_D277(); break;
        case 0xC606:
            func_C606(); break;
        case 0xD394:
            func_D394(); break;
        case 0xE049:
            func_E049(); break;
        case 0xD00C:
            func_D00C(); break;
        case 0xD00D:
            func_D00D(); break;
        case 0xEDD0:
            func_EDD0(); break;
        case 0xEDD1:
            func_EDD1(); break;
        case 0xF054:
            func_F054(); break;
        case 0xCA5F:
            func_CA5F(); break;
        case 0xCA60:
            func_CA60(); break;
        case 0xF0CB:
            func_F0CB(); break;
        case 0xCA30:
            func_CA30(); break;
        case 0xC957:
            func_C957(); break;
        case 0xC958:
            func_C958(); break;
        case 0xE658:
            func_E658(); break;
        case 0xD3A7:
            func_D3A7(); break;
        case 0xD4DD:
            func_D4DD(); break;
        case 0xC945:
            func_C945(); break;
        case 0xC946:
            func_C946(); break;
        case 0xFCC9:
            func_FCC9(); break;
        case 0xFCCA:
            func_FCCA(); break;
        case 0xE90D:
            func_E90D(); break;
        case 0xE90E:
            func_E90E(); break;
        case 0xD028:
            func_D028(); break;
        case 0xD029:
            func_D029(); break;
        case 0xE959:
            func_E959(); break;
        case 0xE95A:
            func_E95A(); break;
        case 0xC55A:
            func_C55A(); break;
        case 0xD00E:
            func_D00E(); break;
        case 0xC90D:
            func_C90D(); break;
        case 0xD4F1:
            func_D4F1(); break;
        case 0xE661:
            func_E661(); break;
        case 0xC90F:
            func_C90F(); break;
        case 0xC910:
            func_C910(); break;
        case 0xF007:
            func_F007(); break;
        case 0xC907:
            func_C907(); break;
        case 0xE86E:
            func_E86E(); break;
        case 0xE86F:
            func_E86F(); break;
        case 0xDBF1:
            func_DBF1(); break;
        case 0xCB7D:
            func_CB7D(); break;
        case 0xD4CB:
            func_D4CB(); break;
        case 0xD4CC:
            func_D4CC(); break;
        case 0xF06E:
            func_F06E(); break;
        case 0xE802:
            func_E802(); break;
        case 0xE8E8:
            func_E8E8(); break;
        case 0xC806:
            func_C806(); break;
        case 0xCF90:
            func_CF90(); break;
        case 0xCF91:
            func_CF91(); break;
        case 0xF829:
            func_F829(); break;
        case 0xF82A:
            func_F82A(); break;
        case 0xF8A0:
            func_F8A0(); break;
        case 0xF8A1:
            func_F8A1(); break;
        case 0xD339:
            func_D339(); break;
        case 0xD33A:
            func_D33A(); break;
        case 0xD890:
            func_D890(); break;
        case 0xD891:
            func_D891(); break;
        case 0xE029:
            func_E029(); break;
        case 0xD1BD:
            func_D1BD(); break;
        case 0xD1BE:
            func_D1BE(); break;
        case 0xE0E9:
            func_E0E9(); break;
        case 0xEE91:
            func_EE91(); break;
        case 0xC031:
            func_C031(); break;
        case 0xE6C0:
            func_E6C0(); break;
        case 0xE6C1:
            func_E6C1(); break;
        case 0xD504:
            func_D504(); break;
        case 0xEEF0:
            func_EEF0(); break;
        case 0xEEF1:
            func_EEF1(); break;
        case 0xF006:
            func_F006(); break;
        case 0xD619:
            func_D619(); break;
        case 0xD61B:
            func_D61B(); break;
        case 0xD61C:
            func_D61C(); break;
        case 0xD06E:
            func_D06E(); break;
        case 0xD06F:
            func_D06F(); break;
        case 0xE809:
            func_E809(); break;
        case 0xE80A:
            func_E80A(); break;
        case 0xC590:
            func_C590(); break;
        case 0xC591:
            func_C591(); break;
        case 0xC891:
            func_C891(); break;
        case 0xE690:
            func_E690(); break;
        case 0xD074:
            func_D074(); break;
        case 0xC6AA:
            func_C6AA(); break;
        case 0xC6AB:
            func_C6AB(); break;
        case 0xF310:
            func_F310(); break;
        case 0xF311:
            func_F311(); break;
        case 0xD650:
            func_D650(); break;
        case 0xD651:
            func_D651(); break;
        case 0xD6B0:
            func_D6B0(); break;
        case 0xD6B1:
            func_D6B1(); break;
        case 0xD6D6:
            func_D6D6(); break;
        case 0xD6D7:
            func_D6D7(); break;
        case 0xDDB7:
            func_DDB7(); break;
        case 0xDDB8:
            func_DDB8(); break;
        case 0xEFDD:
            func_EFDD(); break;
        case 0xD6F0:
            func_D6F0(); break;
        case 0xF0D7:
            func_F0D7(); break;
        case 0xEFBE:
            func_EFBE(); break;
        case 0xC98D:
            func_C98D(); break;
        case 0xD5A6:
            func_D5A6(); break;
        case 0xD5A7:
            func_D5A7(); break;
        case 0xD5A5:
            func_D5A5(); break;
        case 0xD76A:
            func_D76A(); break;
        case 0xD76C:
            func_D76C(); break;
        case 0xD565:
            func_D565(); break;
        case 0xD566:
            func_D566(); break;
        case 0xD586:
            func_D586(); break;
        case 0xD587:
            func_D587(); break;
        case 0xD76B:
            func_D76B(); break;
        case 0xD985:
            func_D985(); break;
        case 0xD986:
            func_D986(); break;
        case 0xD886:
            func_D886(); break;
        case 0xCACA:
            func_CACA(); break;
        case 0xCACB:
            func_CACB(); break;
        case 0xD76F:
            func_D76F(); break;
        case 0xC963:
            func_C963(); break;
        case 0xD8A6:
            func_D8A6(); break;
        case 0xD8A7:
            func_D8A7(); break;
        case 0xD7AF:
            func_D7AF(); break;
        case 0xD7B0:
            func_D7B0(); break;
        case 0xD9C6:
            func_D9C6(); break;
        case 0xD9C7:
            func_D9C7(); break;
        case 0xD0D9:
            func_D0D9(); break;
        case 0xD0DA:
            func_D0DA(); break;
        case 0xD9D0:
            func_D9D0(); break;
        case 0xD9D1:
            func_D9D1(); break;
        case 0xD485:
            func_D485(); break;
        case 0xD486:
            func_D486(); break;
        case 0xCFAF:
            func_CFAF(); break;
        case 0xCEAE:
            func_CEAE(); break;
        case 0xD8AD:
            func_D8AD(); break;
        case 0xD82E:
            func_D82E(); break;
        case 0xE80E:
            func_E80E(); break;
        case 0xF3BD:
            func_F3BD(); break;
        case 0xF3BE:
            func_F3BE(); break;
        case 0xD6F3:
            func_D6F3(); break;
        case 0xD6F4:
            func_D6F4(); break;
        case 0xE8AC:
            func_E8AC(); break;
        case 0xC009:
            func_C009(); break;
        case 0xC00A:
            func_C00A(); break;
        case 0xFCC0:
            func_FCC0(); break;
        case 0xFCC1:
            func_FCC1(); break;
        case 0xF3FC:
            func_F3FC(); break;
        case 0xF3FD:
            func_F3FD(); break;
        case 0xCFF3:
            func_CFF3(); break;
        case 0xE92E:
            func_E92E(); break;
        case 0xE92F:
            func_E92F(); break;
        case 0xEA19:
            func_EA19(); break;
        case 0xD8EA:
            func_D8EA(); break;
        case 0xD8EB:
            func_D8EB(); break;
        case 0xDB8D:
            func_DB8D(); break;
        case 0xDD8D:
            func_DD8D(); break;
        case 0xDE8D:
            func_DE8D(); break;
        case 0xDA43:
            func_DA43(); break;
        case 0xEE21:
            func_EE21(); break;
        case 0xD9D7:
            func_D9D7(); break;
        case 0xDDAD:
            func_DDAD(); break;
        case 0xDBAD:
            func_DBAD(); break;
        case 0xEE03:
            func_EE03(); break;
        case 0xEE04:
            func_EE04(); break;
        case 0xDBEF:
            func_DBEF(); break;
        case 0xDA30:
            func_DA30(); break;
        case 0xDB0B:
            func_DB0B(); break;
        case 0xD942:
            func_D942(); break;
        case 0xF0D0:
            func_F0D0(); break;
        case 0xF3D0:
            func_F3D0(); break;
        case 0xF3D1:
            func_F3D1(); break;
        case 0xDB04:
            func_DB04(); break;
        case 0xDB05:
            func_DB05(); break;
        case 0xDEAD:
            func_DEAD(); break;
        case 0xDEAE:
            func_DEAE(); break;
        case 0xFAA9:
            func_FAA9(); break;
        case 0xFAAA:
            func_FAAA(); break;
        case 0xDEAC:
            func_DEAC(); break;
        case 0xDA21:
            func_DA21(); break;
        case 0xDA22:
            func_DA22(); break;
        case 0xDEEE:
            func_DEEE(); break;
        case 0xDEEF:
            func_DEEF(); break;
        case 0xDDEE:
            func_DDEE(); break;
        case 0xDDEF:
            func_DDEF(); break;
        case 0xF390:
            func_F390(); break;
        case 0xF391:
            func_F391(); break;
        case 0xDCAD:
            func_DCAD(); break;
        case 0xDCAE:
            func_DCAE(); break;
        case 0xDC8D:
            func_DC8D(); break;
        case 0xD050:
            func_D050(); break;
        case 0xD051:
            func_D051(); break;
        case 0xCAF8:
            func_CAF8(); break;
        case 0xCE81:
            func_CE81(); break;
        case 0xDE67:
            func_DE67(); break;
        case 0xDF65:
            func_DF65(); break;
        case 0xDAFE:
            func_DAFE(); break;
        case 0xDAFF:
            func_DAFF(); break;
        case 0xF521:
            func_F521(); break;
        case 0xDEF6:
            func_DEF6(); break;
        case 0xDD20:
            func_DD20(); break;
        case 0xDDDD:
            func_DDDD(); break;
        case 0xDDDE:
            func_DDDE(); break;
        case 0xEF4C:
            func_EF4C(); break;
        case 0xEF29:
            func_EF29(); break;
        case 0xEF2A:
            func_EF2A(); break;
        case 0xDD62:
            func_DD62(); break;
        case 0xDEA8:
            func_DEA8(); break;
        case 0xC479:
            func_C479(); break;
        case 0xDFC6:
            func_DFC6(); break;
        case 0xE017:
            func_E017(); break;
        case 0xE02C:
            func_E02C(); break;
        case 0xEC4C:
            func_EC4C(); break;
        case 0xEC4D:
            func_EC4D(); break;
        case 0xC231:
            func_C231(); break;
        case 0xF420:
            func_F420(); break;
        case 0xC1B5:
            func_C1B5(); break;
        case 0xDD10:
            func_DD10(); break;
        case 0xDE10:
            func_DE10(); break;
        case 0xDE11:
            func_DE11(); break;
        case 0xDC23:
            func_DC23(); break;
        case 0xC99E:
            func_C99E(); break;
        case 0xC90E:
            func_C90E(); break;
        case 0xC87C:
            func_C87C(); break;
        case 0xC87D:
            func_C87D(); break;
        case 0xCAC8:
            func_CAC8(); break;
        case 0xCAC9:
            func_CAC9(); break;
        case 0xC888:
            func_C888(); break;
        case 0xC889:
            func_C889(); break;
        case 0xC88D:
            func_C88D(); break;
        case 0xC88E:
            func_C88E(); break;
        case 0xCE20:
            func_CE20(); break;
        case 0xCE21:
            func_CE21(); break;
        case 0xD2CF:
            func_D2CF(); break;
        case 0xD0F7:
            func_D0F7(); break;
        case 0xF8EC:
            func_F8EC(); break;
        case 0xD08E:
            func_D08E(); break;
        case 0xD5BD:
            func_D5BD(); break;
        case 0xD5BE:
            func_D5BE(); break;
        case 0xDDD6:
            func_DDD6(); break;
        case 0xCDBD:
            func_CDBD(); break;
        case 0xCDBE:
            func_CDBE(); break;
        case 0xDDCD:
            func_DDCD(); break;
        case 0xDDCE:
            func_DDCE(); break;
        case 0xDDB5:
            func_DDB5(); break;
        case 0xDDB6:
            func_DDB6(); break;
        case 0xDDBD:
            func_DDBD(); break;
        case 0xDDBE:
            func_DDBE(); break;
        case 0xC5BD:
            func_C5BD(); break;
        case 0xC5BE:
            func_C5BE(); break;
        case 0xDA8D:
            func_DA8D(); break;
        case 0xDA8E:
            func_DA8E(); break;
        case 0xDF4C:
            func_DF4C(); break;
        case 0xDF4D:
            func_DF4D(); break;
        case 0xD28D:
            func_D28D(); break;
        case 0xD28E:
            func_D28E(); break;
        case 0xD98E:
            func_D98E(); break;
        case 0xD18D:
            func_D18D(); break;
        case 0xD58D:
            func_D58D(); break;
        case 0xD58E:
            func_D58E(); break;
        case 0xD68D:
            func_D68D(); break;
        case 0xD78D:
            func_D78D(); break;
        case 0xD78E:
            func_D78E(); break;
        case 0xD88D:
            func_D88D(); break;
        case 0xD88E:
            func_D88E(); break;
        case 0xD80D:
            func_D80D(); break;
        case 0xDF34:
            func_DF34(); break;
        case 0xDF35:
            func_DF35(); break;
        case 0xDF3C:
            func_DF3C(); break;
        case 0xDF3D:
            func_DF3D(); break;
        case 0xDC79:
            func_DC79(); break;
        case 0xD9AD:
            func_D9AD(); break;
        case 0xD9AE:
            func_D9AE(); break;
        case 0xCEB9:
            func_CEB9(); break;
        case 0xDAAD:
            func_DAAD(); break;
        case 0xDD4F:
            func_DD4F(); break;
        case 0xD5AE:
            func_D5AE(); break;
        case 0xD5AF:
            func_D5AF(); break;
        case 0xDF44:
            func_DF44(); break;
        case 0xD6AD:
            func_D6AD(); break;
        case 0xD6AE:
            func_D6AE(); break;
        case 0xD7AE:
            func_D7AE(); break;
        case 0xD8AE:
            func_D8AE(); break;
        case 0xEE11:
            func_EE11(); break;
        case 0xEE12:
            func_EE12(); break;
        case 0xCE0A:
            func_CE0A(); break;
        case 0xCE0B:
            func_CE0B(); break;
        case 0xDC4C:
            func_DC4C(); break;
        case 0xDC4D:
            func_DC4D(); break;
        case 0xC924:
            func_C924(); break;
        case 0xC925:
            func_C925(); break;
        case 0xD00B:
            func_D00B(); break;
        case 0xC608:
            func_C608(); break;
        case 0xD01D:
            func_D01D(); break;
        case 0xD01E:
            func_D01E(); break;
        case 0xE637:
            func_E637(); break;
        case 0xFCA9:
            func_FCA9(); break;
        case 0xFCAA:
            func_FCAA(); break;
        case 0xE620:
            func_E620(); break;
        case 0xE621:
            func_E621(); break;
        case 0xE012:
            func_E012(); break;
        case 0xE013:
            func_E013(); break;
        case 0xD025:
            func_D025(); break;
        case 0xF063:
            func_F063(); break;
        case 0xF064:
            func_F064(); break;
        case 0xF4F1:
            func_F4F1(); break;
        case 0xE6E0:
            func_E6E0(); break;
        case 0xE6E1:
            func_E6E1(); break;
        case 0xC9B4:
            func_C9B4(); break;
        case 0xC9B5:
            func_C9B5(); break;
        case 0xE9A0:
            func_E9A0(); break;
        case 0xCAE4:
            func_CAE4(); break;
        case 0xCAE5:
            func_CAE5(); break;
        case 0xCA22:
            func_CA22(); break;
        case 0xE104:
            func_E104(); break;
        case 0xE2C9:
            func_E2C9(); break;
        case 0xED90:
            func_ED90(); break;
        case 0xED91:
            func_ED91(); break;
        case 0xE527:
            func_E527(); break;
        case 0xE95E:
            func_E95E(); break;
        case 0xC04C:
            func_C04C(); break;
        case 0xC04D:
            func_C04D(); break;
        case 0xE9C1:
            func_E9C1(); break;
        case 0xF0AD:
            func_F0AD(); break;
        case 0xC610:
            func_C610(); break;
        case 0xC611:
            func_C611(); break;
        case 0xF03A:
            func_F03A(); break;
        case 0xE280:
            func_E280(); break;
        case 0xECF7:
            func_ECF7(); break;
        case 0xE6AF:
            func_E6AF(); break;
        case 0xE150:
            func_E150(); break;
        case 0xE16C:
            func_E16C(); break;
        case 0xE221:
            func_E221(); break;
        case 0xD711:
            func_D711(); break;
        case 0xD5D0:
            func_D5D0(); break;
        case 0xD5D1:
            func_D5D1(); break;
        case 0xDF29:
            func_DF29(); break;
        case 0xE292:
            func_E292(); break;
        case 0xF0E6:
            func_F0E6(); break;
        case 0xF0E7:
            func_F0E7(); break;
        case 0xE21B:
            func_E21B(); break;
        case 0xF1C9:
            func_F1C9(); break;
        case 0xF1CA:
            func_F1CA(); break;
        case 0xE628:
            func_E628(); break;
        case 0xE920:
            func_E920(); break;
        case 0xE921:
            func_E921(); break;
        case 0xE8EA:
            func_E8EA(); break;
        case 0xE6E8:
            func_E6E8(); break;
        case 0xE6E9:
            func_E6E9(); break;
        case 0xE59E:
            func_E59E(); break;
        case 0xE59F:
            func_E59F(); break;
        case 0xDCD0:
            func_DCD0(); break;
        case 0xDCD1:
            func_DCD1(); break;
        case 0xC9A9:
            func_C9A9(); break;
        case 0xC9AA:
            func_C9AA(); break;
        case 0xE9AA:
            func_E9AA(); break;
        case 0xE9AB:
            func_E9AB(); break;
        case 0xC47D:
            func_C47D(); break;
        case 0xC47E:
            func_C47E(); break;
        case 0xE2F5:
            func_E2F5(); break;
        case 0xE39A:
            func_E39A(); break;
        case 0xDA29:
            func_DA29(); break;
        case 0xD0E7:
            func_D0E7(); break;
        case 0xE635:
            func_E635(); break;
        case 0xE32C:
            func_E32C(); break;
        case 0xE9A1:
            func_E9A1(); break;
        case 0xE9A2:
            func_E9A2(); break;
        case 0xC6E8:
            func_C6E8(); break;
        case 0xC6E9:
            func_C6E9(); break;
        case 0xE63D:
            func_E63D(); break;
        case 0xE63E:
            func_E63E(); break;
        case 0xE37A:
            func_E37A(); break;
        case 0xC9A2:
            func_C9A2(); break;
        case 0xC1C9:
            func_C1C9(); break;
        case 0xC1CA:
            func_C1CA(); break;
        case 0xC9A6:
            func_C9A6(); break;
        case 0xC9A7:
            func_C9A7(); break;
        case 0xE43B:
            func_E43B(); break;
        case 0xE4F7:
            func_E4F7(); break;
        case 0xF0B7:
            func_F0B7(); break;
        case 0xC9B1:
            func_C9B1(); break;
        case 0xE445:
            func_E445(); break;
        case 0xFC4C:
            func_FC4C(); break;
        case 0xFC4D:
            func_FC4D(); break;
        case 0xE3FD:
            func_E3FD(); break;
        case 0xE42D:
            func_E42D(); break;
        case 0xFC2A:
            func_FC2A(); break;
        case 0xE610:
            func_E610(); break;
        case 0xE611:
            func_E611(); break;
        case 0xE0A7:
            func_E0A7(); break;
        case 0xD6FD:
            func_D6FD(); break;
        case 0xD6FE:
            func_D6FE(); break;
        case 0xE4D6:
            func_E4D6(); break;
        case 0xE49B:
            func_E49B(); break;
        case 0xE0F0:
            func_E0F0(); break;
        case 0xE0F1:
            func_E0F1(); break;
        case 0xD0A6:
            func_D0A6(); break;
        case 0xD0A7:
            func_D0A7(); break;
        case 0xD67D:
            func_D67D(); break;
        case 0xD67E:
            func_D67E(); break;
        case 0xE8A7:
            func_E8A7(); break;
        case 0xC94C:
            func_C94C(); break;
        case 0xC94D:
            func_C94D(); break;
        case 0xE4CA:
            func_E4CA(); break;
        case 0xE524:
            func_E524(); break;
        case 0xC9B6:
            func_C9B6(); break;
        case 0xC9B7:
            func_C9B7(); break;
        case 0xE87D:
            func_E87D(); break;
        case 0xC96C:
            func_C96C(); break;
        case 0xDD65:
            func_DD65(); break;
        case 0xDD66:
            func_DD66(); break;
        case 0xE569:
            func_E569(); break;
        case 0xF0E5:
            func_F0E5(); break;
        case 0xE571:
            func_E571(); break;
        case 0xCDE5:
            func_CDE5(); break;
        case 0xD1CD:
            func_D1CD(); break;
        case 0xD1CE:
            func_D1CE(); break;
        case 0xDA8F:
            func_DA8F(); break;
        case 0xE613:
            func_E613(); break;
        case 0xE614:
            func_E614(); break;
        case 0xE5FF:
            func_E5FF(); break;
        case 0xEA51:
            func_EA51(); break;
        case 0xDBB9:
            func_DBB9(); break;
        case 0xE5DB:
            func_E5DB(); break;
        case 0xE7B9:
            func_E7B9(); break;
        case 0xE7BA:
            func_E7BA(); break;
        case 0xE5E7:
            func_E5E7(); break;
        case 0xE5E8:
            func_E5E8(); break;
        case 0xF3B9:
            func_F3B9(); break;
        case 0xF3BA:
            func_F3BA(); break;
        case 0xE5F3:
            func_E5F3(); break;
        case 0xE5F4:
            func_E5F4(); break;
        case 0xC900:
            func_C900(); break;
        case 0xC901:
            func_C901(); break;
        case 0xF6BD:
            func_F6BD(); break;
        case 0xE880:
            func_E880(); break;
        case 0xE8B7:
            func_E8B7(); break;
        case 0xCAB0:
            func_CAB0(); break;
        case 0xE6BC:
            func_E6BC(); break;
        case 0xF08A:
            func_F08A(); break;
        case 0xF08B:
            func_F08B(); break;
        case 0xC6F0:
            func_C6F0(); break;
        case 0xCAC6:
            func_CAC6(); break;
        case 0xCAC7:
            func_CAC7(); break;
        case 0xCA8D:
            func_CA8D(); break;
        case 0xCA8E:
            func_CA8E(); break;
        case 0xE8C7:
            func_E8C7(); break;
        case 0xE8B3:
            func_E8B3(); break;
        case 0xE80F:
            func_E80F(); break;
        case 0xDA4C:
            func_DA4C(); break;
        case 0xDA4D:
            func_DA4D(); break;
        case 0xC545:
            func_C545(); break;
        case 0xC546:
            func_C546(); break;
        case 0xC831:
            func_C831(); break;
        case 0xC832:
            func_C832(); break;
        case 0xC502:
            func_C502(); break;
        case 0xC503:
            func_C503(); break;
        case 0xD06A:
            func_D06A(); break;
        case 0xD06B:
            func_D06B(); break;
        case 0xC82A:
            func_C82A(); break;
        case 0xC86C:
            func_C86C(); break;
        case 0xC024:
            func_C024(); break;
        case 0xC025:
            func_C025(); break;
        case 0xC866:
            func_C866(); break;
        case 0xE867:
            func_E867(); break;
        case 0xE816:
            func_E816(); break;
        case 0xD9B9:
            func_D9B9(); break;
        case 0xD9BA:
            func_D9BA(); break;
        case 0xE8D9:
            func_E8D9(); break;
        case 0xE8DA:
            func_E8DA(); break;
        case 0xC9B8:
            func_C9B8(); break;
        case 0xC90A:
            func_C90A(); break;
        case 0xF00A:
            func_F00A(); break;
        case 0xF00B:
            func_F00B(); break;
        case 0xCE4C:
            func_CE4C(); break;
        case 0xD6CF:
            func_D6CF(); break;
        case 0xE9BF:
            func_E9BF(); break;
        case 0xE623:
            func_E623(); break;
        case 0xE624:
            func_E624(); break;
        case 0xD7E6:
            func_D7E6(); break;
        case 0xD7E7:
            func_D7E7(); break;
        case 0xD7A5:
            func_D7A5(); break;
        case 0xD7A6:
            func_D7A6(); break;
        case 0xC9D8:
            func_C9D8(); break;
        case 0xF54C:
            func_F54C(); break;
        case 0xF54D:
            func_F54D(); break;
        case 0xD6F6:
            func_D6F6(); break;
        case 0xD785:
            func_D785(); break;
        case 0xD786:
            func_D786(); break;
        case 0xC93B:
            func_C93B(); break;
        case 0xEA38:
            func_EA38(); break;
        case 0xC51D:
            func_C51D(); break;
        case 0xC812:
            func_C812(); break;
        case 0xC813:
            func_C813(); break;
        case 0xC86D:
            func_C86D(); break;
        case 0xC8DB:
            func_C8DB(); break;
        case 0xEA48:
            func_EA48(); break;
        case 0xD2AD:
            func_D2AD(); break;
        case 0xD2AE:
            func_D2AE(); break;
        case 0xEBF1:
            func_EBF1(); break;
        case 0xEA9C:
            func_EA9C(); break;
        case 0xEA9E:
            func_EA9E(); break;
        case 0xC522:
            func_C522(); break;
        case 0xC523:
            func_C523(); break;
        case 0xC818:
            func_C818(); break;
        case 0xC825:
            func_C825(); break;
        case 0xEAAC:
            func_EAAC(); break;
        case 0xEB03:
            func_EB03(); break;
        case 0xC6EC:
            func_C6EC(); break;
        case 0xEAC6:
            func_EAC6(); break;
        case 0xEAC7:
            func_EAC7(); break;
        case 0xEB18:
            func_EB18(); break;
        case 0xEB41:
            func_EB41(); break;
        case 0xEB3F:
            func_EB3F(); break;
        case 0xEB3D:
            func_EB3D(); break;
        case 0xEB3E:
            func_EB3E(); break;
        case 0xEB51:
            func_EB51(); break;
        case 0xEB60:
            func_EB60(); break;
        case 0xEB61:
            func_EB61(); break;
        case 0xEB70:
            func_EB70(); break;
        case 0xEB71:
            func_EB71(); break;
        case 0xEB80:
            func_EB80(); break;
        case 0xEB81:
            func_EB81(); break;
        case 0xEB90:
            func_EB90(); break;
        case 0xEB91:
            func_EB91(); break;
        case 0xEBA0:
            func_EBA0(); break;
        case 0xEBA1:
            func_EBA1(); break;
        case 0xEBB0:
            func_EBB0(); break;
        case 0xEBB1:
            func_EBB1(); break;
        case 0xC0EC:
            func_C0EC(); break;
        case 0xEBC0:
            func_EBC0(); break;
        case 0xEBC1:
            func_EBC1(); break;
        case 0xC7AD:
            func_C7AD(); break;
        case 0xC917:
            func_C917(); break;
        case 0xC918:
            func_C918(); break;
        case 0xEC22:
            func_EC22(); break;
        case 0xEC52:
            func_EC52(); break;
        case 0xECAD:
            func_ECAD(); break;
        case 0xEC49:
            func_EC49(); break;
        case 0xEC4A:
            func_EC4A(); break;
        case 0xEC59:
            func_EC59(); break;
        case 0xC9AF:
            func_C9AF(); break;
        case 0xECA2:
            func_ECA2(); break;
        case 0xECA3:
            func_ECA3(); break;
        case 0xC506:
            func_C506(); break;
        case 0xD09E:
            func_D09E(); break;
        case 0xD09F:
            func_D09F(); break;
        case 0xF860:
            func_F860(); break;
        case 0xF861:
            func_F861(); break;
        case 0xECF4:
            func_ECF4(); break;
        case 0xECEF:
            func_ECEF(); break;
        case 0xECF0:
            func_ECF0(); break;
        case 0xED73:
            func_ED73(); break;
        case 0xEEAA:
            func_EEAA(); break;
        case 0xE6CF:
            func_E6CF(); break;
        case 0xC6A8:
            func_C6A8(); break;
        case 0xC6A9:
            func_C6A9(); break;
        case 0xF411:
            func_F411(); break;
        case 0xED9E:
            func_ED9E(); break;
        case 0xEEC0:
            func_EEC0(); break;
        case 0xEDCE:
            func_EDCE(); break;
        case 0xEE94:
            func_EE94(); break;
        case 0xE6EF:
            func_E6EF(); break;
        case 0xC003:
            func_C003(); break;
        case 0xC004:
            func_C004(); break;
        case 0xEE16:
            func_EE16(); break;
        case 0xC8AD:
            func_C8AD(); break;
        case 0xC8AE:
            func_C8AE(); break;
        case 0xC1BD:
            func_C1BD(); break;
        case 0xEDC2:
            func_EDC2(); break;
        case 0xC5B9:
            func_C5B9(); break;
        case 0xC5BA:
            func_C5BA(); break;
        case 0xC6BA:
            func_C6BA(); break;
        case 0xEE40:
            func_EE40(); break;
        case 0xEE6A:
            func_EE6A(); break;
        case 0xC848:
            func_C848(); break;
        case 0xC849:
            func_C849(); break;
        case 0xD24D:
            func_D24D(); break;
        case 0xEED3:
            func_EED3(); break;
        case 0xEF65:
            func_EF65(); break;
        case 0xEF63:
            func_EF63(); break;
        case 0xEF69:
            func_EF69(); break;
        case 0xEF9D:
            func_EF9D(); break;
        case 0xEF9E:
            func_EF9E(); break;
        case 0xD3EF:
            func_D3EF(); break;
        case 0xEFD3:
            func_EFD3(); break;
        case 0xEFD4:
            func_EFD4(); break;
        case 0xD585:
            func_D585(); break;
        case 0xF820:
            func_F820(); break;
        case 0xF821:
            func_F821(); break;
        case 0xEFF8:
            func_EFF8(); break;
        case 0xD9AC:
            func_D9AC(); break;
        case 0xCCB9:
            func_CCB9(); break;
        case 0xCCBA:
            func_CCBA(); break;
        case 0xF110:
            func_F110(); break;
        case 0xF111:
            func_F111(); break;
        case 0xC83B:
            func_C83B(); break;
        case 0xC83F:
            func_C83F(); break;
        case 0xC840:
            func_C840(); break;
        case 0xF182:
            func_F182(); break;
        case 0xD039:
            func_D039(); break;
        case 0xD03A:
            func_D03A(); break;
        case 0xF23D:
            func_F23D(); break;
        case 0xF23E:
            func_F23E(); break;
        case 0xF224:
            func_F224(); break;
        case 0xF0F2:
            func_F0F2(); break;
        case 0xF0F3:
            func_F0F3(); break;
        case 0xF229:
            func_F229(); break;
        case 0xC642:
            func_C642(); break;
        case 0xC643:
            func_C643(); break;
        case 0xE640:
            func_E640(); break;
        case 0xC644:
            func_C644(); break;
        case 0xF14C:
            func_F14C(); break;
        case 0xF14D:
            func_F14D(); break;
        case 0xF227:
            func_F227(); break;
        case 0xF176:
            func_F176(); break;
        case 0xE320:
            func_E320(); break;
        case 0xE321:
            func_E321(); break;
        case 0xF2E4:
            func_F2E4(); break;
        case 0xD4AD:
            func_D4AD(); break;
        case 0xD4AE:
            func_D4AE(); break;
        case 0xD38D:
            func_D38D(); break;
        case 0xF317:
            func_F317(); break;
        case 0xF4D0:
            func_F4D0(); break;
        case 0xF4D1:
            func_F4D1(); break;
        case 0xD3AD:
            func_D3AD(); break;
        case 0xC28C:
            func_C28C(); break;
        case 0xF830:
            func_F830(); break;
        case 0xF831:
            func_F831(); break;
        case 0xD520:
            func_D520(); break;
        case 0xD521:
            func_D521(); break;
        case 0xF2D5:
            func_F2D5(); break;
        case 0xDF7D:
            func_DF7D(); break;
        case 0xF2DF:
            func_F2DF(); break;
        case 0xE17D:
            func_E17D(); break;
        case 0xE17E:
            func_E17E(); break;
        case 0xC76D:
            func_C76D(); break;
        case 0xC76E:
            func_C76E(); break;
        case 0xF388:
            func_F388(); break;
        case 0xF389:
            func_F389(); break;
        case 0xDDF3:
            func_DDF3(); break;
        case 0xF0F4:
            func_F0F4(); break;
        case 0xFB86:
            func_FB86(); break;
        case 0xFB87:
            func_FB87(); break;
        case 0xEC85:
            func_EC85(); break;
        case 0xEC86:
            func_EC86(); break;
        case 0xED85:
            func_ED85(); break;
        case 0xED86:
            func_ED86(); break;
        case 0xF3DD:
            func_F3DD(); break;
        case 0xEDE7:
            func_EDE7(); break;
        case 0xCAEC:
            func_CAEC(); break;
        case 0xECD0:
            func_ECD0(); break;
        case 0xECD1:
            func_ECD1(); break;
        case 0xECB1:
            func_ECB1(); break;
        case 0xECB2:
            func_ECB2(); break;
        case 0xF3F5:
            func_F3F5(); break;
        case 0xF47D:
            func_F47D(); break;
        case 0xF47E:
            func_F47E(); break;
        case 0xEC87:
            func_EC87(); break;
        case 0xED87:
            func_ED87(); break;
        case 0xC9ED:
            func_C9ED(); break;
        case 0xC9EE:
            func_C9EE(); break;
        case 0xCAF6:
            func_CAF6(); break;
        case 0xEDA6:
            func_EDA6(); break;
        case 0xF84B:
            func_F84B(); break;
        case 0xF827:
            func_F827(); break;
        case 0xEFD0:
            func_EFD0(); break;
        case 0xEFD1:
            func_EFD1(); break;
        case 0xEECD:
            func_EECD(); break;
        case 0xF491:
            func_F491(); break;
        case 0xF4A2:
            func_F4A2(); break;
        case 0xCFF0:
            func_CFF0(); break;
        case 0xCFF1:
            func_CFF1(); break;
        case 0xCAD0:
            func_CAD0(); break;
        case 0xC921:
            func_C921(); break;
        case 0xC922:
            func_C922(); break;
        case 0xEC06:
            func_EC06(); break;
        case 0xF649:
            func_F649(); break;
        case 0xEEF6:
            func_EEF6(); break;
        case 0xEEF7:
            func_EEF7(); break;
        case 0xC9EC:
            func_C9EC(); break;
        case 0xC975:
            func_C975(); break;
        case 0xC976:
            func_C976(); break;
        case 0xF0FE:
            func_F0FE(); break;
        case 0xC93D:
            func_C93D(); break;
        case 0xFBC9:
            func_FBC9(); break;
        case 0xFBCA:
            func_FBCA(); break;
        case 0xF0FC:
            func_F0FC(); break;
        case 0xC96F:
            func_C96F(); break;
        case 0xF321:
            func_F321(); break;
        case 0xF5F3:
            func_F5F3(); break;
        case 0xF5F4:
            func_F5F4(); break;
        case 0xC939:
            func_C939(); break;
        case 0xEAD1:
            func_EAD1(); break;
        case 0xF34C:
            func_F34C(); break;
        case 0xF34D:
            func_F34D(); break;
        case 0xF4F3:
            func_F4F3(); break;
        case 0xEA85:
            func_EA85(); break;
        case 0xEB86:
            func_EB86(); break;
        case 0xF805:
            func_F805(); break;
        case 0xF5CD:
            func_F5CD(); break;
        case 0xF5CE:
            func_F5CE(); break;
        case 0xF81F:
            func_F81F(); break;
        case 0xEBE6:
            func_EBE6(); break;
        case 0xEBE7:
            func_EBE7(); break;
        case 0xE6EB:
            func_E6EB(); break;
        case 0xD120:
            func_D120(); break;
        case 0xD121:
            func_D121(); break;
        case 0xF5D2:
            func_F5D2(); break;
        case 0xE8F5:
            func_E8F5(); break;
        case 0xE861:
            func_E861(); break;
        case 0xF846:
            func_F846(); break;
        case 0xED26:
            func_ED26(); break;
        case 0xF63E:
            func_F63E(); break;
        case 0xF63F:
            func_F63F(); break;
        case 0xF843:
            func_F843(); break;
        case 0xC00D:
            func_C00D(); break;
        case 0xD427:
            func_D427(); break;
        case 0xF046:
            func_F046(); break;
        case 0xF047:
            func_F047(); break;
        case 0xF4AF:
            func_F4AF(); break;
        case 0xCC0D:
            func_CC0D(); break;
        case 0xC829:
            func_C829(); break;
        case 0xEBAE:
            func_EBAE(); break;
        case 0xF78D:
            func_F78D(); break;
        case 0xEA0D:
            func_EA0D(); break;
        case 0xEA0E:
            func_EA0E(); break;
        case 0xF64C:
            func_F64C(); break;
        case 0xF7F7:
            func_F7F7(); break;
        case 0xE926:
            func_E926(); break;
        case 0xE927:
            func_E927(); break;
        case 0xE9E6:
            func_E9E6(); break;
        case 0xE9E7:
            func_E9E7(); break;
        case 0xDE85:
            func_DE85(); break;
        case 0xDE86:
            func_DE86(); break;
        case 0xDF86:
            func_DF86(); break;
        case 0xDF87:
            func_DF87(); break;
        case 0xE084:
            func_E084(); break;
        case 0xE085:
            func_E085(); break;
        case 0xEE85:
            func_EE85(); break;
        case 0xEE86:
            func_EE86(); break;
        case 0xEEA6:
            func_EEA6(); break;
        case 0xEF85:
            func_EF85(); break;
        case 0xF8A9:
            func_F8A9(); break;
        case 0xF8AA:
            func_F8AA(); break;
        case 0xC5AA:
            func_C5AA(); break;
        case 0xEFA5:
            func_EFA5(); break;
        case 0xEFA6:
            func_EFA6(); break;
        case 0xDEA5:
            func_DEA5(); break;
        case 0xDEA6:
            func_DEA6(); break;
        case 0xDFA6:
            func_DFA6(); break;
        case 0xDFA7:
            func_DFA7(); break;
        case 0xE0A5:
            func_E0A5(); break;
        case 0xEC84:
            func_EC84(); break;
        case 0xDBB1:
            func_DBB1(); break;
        case 0xDBB2:
            func_DBB2(); break;
        case 0xDCE6:
            func_DCE6(); break;
        case 0xCADC:
            func_CADC(); break;
        case 0xCADD:
            func_CADD(); break;
        case 0xC6F3:
            func_C6F3(); break;
        case 0xC6F4:
            func_C6F4(); break;
        case 0xECC7:
            func_ECC7(); break;
        case 0xD0EC:
            func_D0EC(); break;
        case 0xEE8D:
            func_EE8D(); break;
        case 0xEE8E:
            func_EE8E(); break;
        case 0xCBBD:
            func_CBBD(); break;
        case 0xCBBE:
            func_CBBE(); break;
        case 0xF8CB:
            func_F8CB(); break;
        case 0xF8CC:
            func_F8CC(); break;
        case 0xD2BA:
            func_D2BA(); break;
        case 0xF8D3:
            func_F8D3(); break;
        case 0xF0F8:
            func_F0F8(); break;
        case 0xC8F5:
            func_C8F5(); break;
        case 0xC8F6:
            func_C8F6(); break;
        case 0xE4D0:
            func_E4D0(); break;
        case 0xE4D1:
            func_E4D1(); break;
        case 0xDB86:
            func_DB86(); break;
        case 0xDC85:
            func_DC85(); break;
        case 0xF89F:
            func_F89F(); break;
        case 0xEDAD:
            func_EDAD(); break;
        case 0xEDAE:
            func_EDAE(); break;
        case 0xDD04:
            func_DD04(); break;
        case 0xF749:
            func_F749(); break;
        case 0xF74B:
            func_F74B(); break;
        case 0xEDEE:
            func_EDEE(); break;
        case 0xEDEF:
            func_EDEF(); break;
        case 0xEC65:
            func_EC65(); break;
        case 0xEC66:
            func_EC66(); break;
        case 0xED65:
            func_ED65(); break;
        case 0xED66:
            func_ED66(); break;
        case 0xF93D:
            func_F93D(); break;
        case 0xFA07:
            func_FA07(); break;
        case 0xECE5:
            func_ECE5(); break;
        case 0xECE6:
            func_ECE6(); break;
        case 0xE503:
            func_E503(); break;
        case 0xEDE5:
            func_EDE5(); break;
        case 0xE904:
            func_E904(); break;
        case 0xE74D:
            func_E74D(); break;
        case 0xFA48:
            func_FA48(); break;
        case 0xC8F8:
            func_C8F8(); break;
        case 0xC8F9:
            func_C8F9(); break;
        case 0xFA31:
            func_FA31(); break;
        case 0xFA0B:
            func_FA0B(); break;
        case 0xFA0C:
            func_FA0C(); break;
        case 0xE8FB:
            func_E8FB(); break;
        case 0xFA56:
            func_FA56(); break;
        case 0xF510:
            func_F510(); break;
        case 0xF511:
            func_F511(); break;
        case 0xEC07:
            func_EC07(); break;
        case 0xEE26:
            func_EE26(); break;
        case 0xEE27:
            func_EE27(); break;
        case 0xC92A:
            func_C92A(); break;
        case 0xECE7:
            func_ECE7(); break;
        case 0xD0C0:
            func_D0C0(); break;
        case 0xEEAD:
            func_EEAD(); break;
        case 0xEEAE:
            func_EEAE(); break;
        case 0xC50A:
            func_C50A(); break;
        case 0xC50B:
            func_C50B(); break;
        case 0xEEC5:
            func_EEC5(); break;
        case 0xEF84:
            func_EF84(); break;
        case 0xEEAF:
            func_EEAF(); break;
        case 0xF04A:
            func_F04A(); break;
        case 0xFA6E:
            func_FA6E(); break;
        case 0xFA6F:
            func_FA6F(); break;
        case 0xCD69:
            func_CD69(); break;
        case 0xFA71:
            func_FA71(); break;
        case 0xFAD7:
            func_FAD7(); break;
        case 0xFA72:
            func_FA72(); break;
        case 0xFA73:
            func_FA73(); break;
        case 0xFB2F:
            func_FB2F(); break;
        case 0xC8FB:
            func_C8FB(); break;
        case 0xC8FC:
            func_C8FC(); break;
        case 0xFB37:
            func_FB37(); break;
        case 0xFB27:
            func_FB27(); break;
        case 0xFB28:
            func_FB28(); break;
        case 0xC0FF:
            func_C0FF(); break;
        case 0xC0C1:
            func_C0C1(); break;
        case 0xE0FF:
            func_E0FF(); break;
        case 0xE100:
            func_E100(); break;
        case 0xE0E0:
            func_E0E0(); break;
        case 0xE0E1:
            func_E0E1(); break;
        case 0xFFE0:
            func_FFE0(); break;
        case 0xFFE1:
            func_FFE1(); break;
        case 0xF0F0:
            func_F0F0(); break;
        case 0xF8F8:
            func_F8F8(); break;
        case 0xF8F9:
            func_F8F9(); break;
        case 0xFFF8:
            func_FFF8(); break;
        case 0xFFF9:
            func_FFF9(); break;
        case 0xFFFD:
            func_FFFD(); break;
        case 0xE4B9:
            func_E4B9(); break;
        case 0xFBF1:
            func_FBF1(); break;
        case 0xED47:
            func_ED47(); break;
        case 0xE987:
            func_E987(); break;
        case 0xE887:
            func_E887(); break;
        case 0xF786:
            func_F786(); break;
        case 0xFC5B:
            func_FC5B(); break;
        case 0xFC5C:
            func_FC5C(); break;
        case 0xFC60:
            func_FC60(); break;
        case 0xFC61:
            func_FC61(); break;
        case 0xEEB1:
            func_EEB1(); break;
        case 0xEEB2:
            func_EEB2(); break;
        case 0xC0F8:
            func_C0F8(); break;
        case 0xC0F9:
            func_C0F9(); break;
        case 0xDED0:
            func_DED0(); break;
        case 0xDED1:
            func_DED1(); break;
        case 0xC0B0:
            func_C0B0(); break;
        case 0xCAFD:
            func_CAFD(); break;
        case 0xC99A:
            func_C99A(); break;
        case 0xD5C9:
            func_D5C9(); break;
        case 0xD5CA:
            func_D5CA(); break;
        case 0xCA49:
            func_CA49(); break;
        case 0xC179:
            func_C179(); break;
        case 0xFB70:
            func_FB70(); break;
        case 0xC756:
            func_C756(); break;
        case 0xCBA3:
            func_CBA3(); break;
        case 0xD07F:
            func_D07F(); break;
        case 0xA860:
            switch (g_current_bank) {
                case 15: func_E860(); break;
                case 0: func_A860_b0(); break;
                case 1: func_A860_b1(); break;
                case 2: func_A860_b2(); break;
                case 3: func_A860_b3(); break;
                case 4: func_A860_b4(); break;
                case 5: func_A860_b5(); break;
                case 6: func_A860_b6(); break;
                case 7: func_A860_b7(); break;
                case 8: func_A860_b8(); break;
                case 9: func_A860_b9(); break;
                case 10: func_A860_b10(); break;
                case 11: func_A860_b11(); break;
                case 12: func_A860_b12(); break;
                case 13: func_A860_b13(); break;
                case 14: func_A860_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xE7F6:
            func_E7F6(); break;
        case 0x8A24:
            switch (g_current_bank) {
                case 0: func_8A24_b0(); break;
                case 1: func_8A24_b1(); break;
                case 2: func_8A24_b2(); break;
                case 3: func_8A24_b3(); break;
                case 4: func_8A24_b4(); break;
                case 5: func_8A24_b5(); break;
                case 6: func_8A24_b6(); break;
                case 7: func_8A24_b7(); break;
                case 8: func_8A24_b8(); break;
                case 9: func_8A24_b9(); break;
                case 10: func_8A24_b10(); break;
                case 11: func_8A24_b11(); break;
                case 12: func_8A24_b12(); break;
                case 13: func_8A24_b13(); break;
                case 14: func_8A24_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA224:
            switch (g_current_bank) {
                case 0: func_A224_b0(); break;
                case 1: func_A224_b1(); break;
                case 2: func_A224_b2(); break;
                case 3: func_A224_b3(); break;
                case 4: func_A224_b4(); break;
                case 5: func_A224_b5(); break;
                case 6: func_A224_b6(); break;
                case 7: func_A224_b7(); break;
                case 8: func_A224_b8(); break;
                case 9: func_A224_b9(); break;
                case 10: func_A224_b10(); break;
                case 11: func_A224_b11(); break;
                case 12: func_A224_b12(); break;
                case 13: func_A224_b13(); break;
                case 14: func_A224_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xF6F2:
            func_F6F2(); break;
        case 0xE3AF:
            func_E3AF(); break;
        case 0xD16E:
            func_D16E(); break;
        case 0xD18E:
            func_D18E(); break;
        case 0xFB10:
            func_FB10(); break;
        case 0xCD0D:
            func_CD0D(); break;
        case 0xCD94:
            func_CD94(); break;
        case 0xE882:
            func_E882(); break;
        case 0xCA00:
            func_CA00(); break;
        case 0xFA49:
            func_FA49(); break;
        case 0xF9EC:
            func_F9EC(); break;
        case 0xFB63:
            func_FB63(); break;
        case 0xFB65:
            func_FB65(); break;
        case 0xF1AC:
            func_F1AC(); break;
        case 0xF1A8:
            func_F1A8(); break;
        case 0x93BD:
            switch (g_current_bank) {
                case 0: func_93BD_b0(); break;
                case 1: func_93BD_b1(); break;
                case 2: func_93BD_b2(); break;
                case 3: func_93BD_b3(); break;
                case 4: func_93BD_b4(); break;
                case 5: func_93BD_b5(); break;
                case 6: func_93BD_b6(); break;
                case 7: func_93BD_b7(); break;
                case 8: func_93BD_b8(); break;
                case 9: func_93BD_b9(); break;
                case 10: func_93BD_b10(); break;
                case 11: func_93BD_b11(); break;
                case 12: func_93BD_b12(); break;
                case 13: func_93BD_b13(); break;
                case 14: func_93BD_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xDBCA:
            func_DBCA(); break;
        case 0xCF79:
            func_CF79(); break;
        case 0xCFC0:
            func_CFC0(); break;
        case 0xCF9C:
            func_CF9C(); break;
        case 0xD265:
            func_D265(); break;
        case 0xCA5A:
            func_CA5A(); break;
        case 0xE5E6:
            func_E5E6(); break;
        case 0xFCC6:
            func_FCC6(); break;
        case 0xD022:
            func_D022(); break;
        case 0xC7B5:
            func_C7B5(); break;
        case 0xCF63:
            func_CF63(); break;
        case 0xD6D4:
            func_D6D4(); break;
        case 0xDD49:
            func_DD49(); break;
        case 0xDD4B:
            func_DD4B(); break;
        case 0xDD50:
            func_DD50(); break;
        case 0xDD53:
            func_DD53(); break;
        case 0xDD55:
            func_DD55(); break;
        case 0xD593:
            func_D593(); break;
        case 0xD52C:
            func_D52C(); break;
        case 0xD868:
            func_D868(); break;
        case 0xD477:
            func_D477(); break;
        case 0xCEA4:
            func_CEA4(); break;
        case 0x8DAE:
            switch (g_current_bank) {
                case 0: func_8DAE_b0(); break;
                case 1: func_8DAE_b1(); break;
                case 2: func_8DAE_b2(); break;
                case 3: func_8DAE_b3(); break;
                case 4: func_8DAE_b4(); break;
                case 5: func_8DAE_b5(); break;
                case 6: func_8DAE_b6(); break;
                case 7: func_8DAE_b7(); break;
                case 8: func_8DAE_b8(); break;
                case 9: func_8DAE_b9(); break;
                case 10: func_8DAE_b10(); break;
                case 11: func_8DAE_b11(); break;
                case 12: func_8DAE_b12(); break;
                case 13: func_8DAE_b13(); break;
                case 14: func_8DAE_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xDA9A:
            func_DA9A(); break;
        case 0xF3C2:
            func_F3C2(); break;
        case 0xDE3E:
            func_DE3E(); break;
        case 0xD9D3:
            func_D9D3(); break;
        case 0xF4C8:
            func_F4C8(); break;
        case 0xEF25:
            func_EF25(); break;
        case 0xF414:
            func_F414(); break;
        case 0xD544:
            func_D544(); break;
        case 0xDD41:
            func_DD41(); break;
        case 0xD283:
            func_D283(); break;
        case 0xD189:
            func_D189(); break;
        case 0xD58B:
            func_D58B(); break;
        case 0xD686:
            func_D686(); break;
        case 0xD783:
            func_D783(); break;
        case 0xD970:
            func_D970(); break;
        case 0xDD12:
            func_DD12(); break;
        case 0xC04A:
            func_C04A(); break;
        case 0xE949:
            func_E949(); break;
        case 0xC952:
            func_C952(); break;
        case 0xFC36:
            func_FC36(); break;
        case 0xE453:
            func_E453(); break;
        case 0xC890:
            func_C890(); break;
        case 0xC7DD:
            func_C7DD(); break;
        case 0xC4DA:
            func_C4DA(); break;
        case 0xC495:
            func_C495(); break;
        case 0xD9B1:
            func_D9B1(); break;
        case 0xE966:
            func_E966(); break;
        case 0xEB2E:
            func_EB2E(); break;
        case 0xC7F3:
            func_C7F3(); break;
        case 0xD3EA:
            func_D3EA(); break;
        case 0xC737:
            func_C737(); break;
        case 0xC70A:
            func_C70A(); break;
        case 0xC72A:
            func_C72A(); break;
        case 0xC74A:
            func_C74A(); break;
        case 0xF465:
            func_F465(); break;
        case 0xF7F1:
            func_F7F1(); break;
        case 0xD11C:
            func_D11C(); break;
        case 0xC8F3:
            func_C8F3(); break;
        case 0xC4B5:
            func_C4B5(); break;
        case 0xCD56:
            func_CD56(); break;
        case 0xC0FE:
            func_C0FE(); break;
        case 0x80A0:
            switch (g_current_bank) {
                case 0: func_80A0_b0(); break;
                case 1: func_80A0_b1(); break;
                case 2: func_80A0_b2(); break;
                case 3: func_80A0_b3(); break;
                case 4: func_80A0_b4(); break;
                case 5: func_80A0_b5(); break;
                case 6: func_80A0_b6(); break;
                case 7: func_80A0_b7(); break;
                case 8: func_80A0_b8(); break;
                case 9: func_80A0_b9(); break;
                case 10: func_80A0_b10(); break;
                case 11: func_80A0_b11(); break;
                case 12: func_80A0_b12(); break;
                case 13: func_80A0_b13(); break;
                case 14: func_80A0_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xFC1E:
            func_FC1E(); break;
        case 0xFC44:
            func_FC44(); break;
        case 0xF3CE:
            func_F3CE(); break;
        case 0xCDD5:
            func_CDD5(); break;
        case 0xC0CE:
            func_C0CE(); break;
        case 0x931C:
            func_931C_b1(); break;
        case 0xA85E:
            func_A85E_b2(); break;
        case 0xDCCB:
            func_DCCB(); break;
        case 0xC9C5:
            func_C9C5(); break;
        case 0xCAC5:
            func_CAC5(); break;
        case 0xA85C:
            func_A85C_b12(); break;
        case 0xA836:
            func_A836_b12(); break;
        case 0xA99C:
            func_A99C_b12(); break;
        case 0xA7F1:
            func_A7F1_b12(); break;
        case 0xA8F2:
            func_A8F2_b12(); break;
        case 0xA9C9:
            switch (g_current_bank) {
                case 12: func_A9C9_b12(); break;
                case 14: func_A9C9_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA9F2:
            switch (g_current_bank) {
                case 12: func_A9F2_b12(); break;
                case 1: func_A9F2_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAA6C:
            func_AA6C_b12(); break;
        case 0xA9A2:
            func_A9A2_b12(); break;
        case 0xA9CF:
            func_A9CF_b12(); break;
        case 0xAA20:
            func_AA20_b12(); break;
        case 0xAA46:
            func_AA46_b12(); break;
        case 0xA9F8:
            func_A9F8_b12(); break;
        case 0xA879:
            func_A879_b14(); break;
        case 0xC9A0:
            func_C9A0(); break;
        case 0xB3D3:
            func_B3D3_b1(); break;
        case 0x8A1A:
            func_8A1A_b8(); break;
        case 0x89F8:
            func_89F8_b10(); break;
        case 0xFF84:
            func_FF84(); break;
        case 0xA920:
            switch (g_current_bank) {
                case 15: func_E920(); break;
                case 12: func_A920_b12(); break;
                case 14: func_A920_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x96FE:
            func_96FE_b12(); break;
        case 0x976C:
            func_976C_b12(); break;
        case 0x9757:
            func_9757_b12(); break;
        case 0x980F:
            func_980F_b12(); break;
        case 0x982A:
            func_982A_b12(); break;
        case 0x99BE:
            func_99BE_b12(); break;
        case 0x99A1:
            func_99A1_b12(); break;
        case 0x9949:
            func_9949_b12(); break;
        case 0xF539:
            func_F539(); break;
        case 0x99DB:
            func_99DB_b12(); break;
        case 0xFA26:
            func_FA26(); break;
        case 0xA1CC:
            func_A1CC_b1(); break;
        case 0xDAF9:
            func_DAF9(); break;
        case 0xF2C5:
            func_F2C5(); break;
        case 0xA1F0:
            func_A1F0_b2(); break;
        case 0xA1FC:
            func_A1FC_b10(); break;
        case 0x9108:
            func_9108_b10(); break;
        case 0xF7FB:
            func_F7FB(); break;
        case 0x8800:
            switch (g_current_bank) {
                case 15: func_C800(); break;
                case 10: func_8800_b10(); break;
                case 7: func_8800_b7(); break;
                case 12: func_8800_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA0D0:
            switch (g_current_bank) {
                case 10: func_A0D0_b10(); break;
                case 6: func_A0D0_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xF973:
            func_F973(); break;
        case 0x93B6:
            func_93B6_b2(); break;
        case 0x93AA:
            func_93AA_b2(); break;
        case 0x8C00:
            switch (g_current_bank) {
                case 5: func_8C00_b5(); break;
                case 3: func_8C00_b3(); break;
                case 6: func_8C00_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x93B2:
            switch (g_current_bank) {
                case 10: func_93B2_b10(); break;
                case 2: func_93B2_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x93BC:
            func_93BC_b10(); break;
        case 0x8C82:
            func_8C82_b14(); break;
        case 0x8C8E:
            func_8C8E_b14(); break;
        case 0xD458:
            func_D458(); break;
        case 0x8DA2:
            func_8DA2_b6(); break;
        case 0xA894:
            func_A894_b14(); break;
        case 0x85CA:
            switch (g_current_bank) {
                case 14: func_85CA_b14(); break;
                case 1: func_85CA_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x861F:
            switch (g_current_bank) {
                case 15: func_C61F(); break;
                case 14: func_861F_b14(); break;
                case 12: func_861F_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x864A:
            func_864A_b14(); break;
        case 0xD944:
            func_D944(); break;
        case 0x8080:
            switch (g_current_bank) {
                case 15: func_C080(); break;
                case 2: func_8080_b2(); break;
                case 14: func_8080_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x808F:
            func_808F_b2(); break;
        case 0x8074:
            switch (g_current_bank) {
                case 6: func_8074_b6(); break;
                case 0: func_8074_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8603:
            func_8603_b12(); break;
        case 0xA932:
            func_A932_b12(); break;
        case 0x87B0:
            func_87B0_b12(); break;
        case 0xF281:
            func_F281(); break;
        case 0x822B:
            func_822B_b12(); break;
        case 0x81FB:
            func_81FB_b12(); break;
        case 0xF466:
            func_F466(); break;
        case 0x992A:
            func_992A_b12(); break;
        case 0x826E:
            func_826E_b12(); break;
        case 0x9956:
            func_9956_b12(); break;
        case 0x9980:
            switch (g_current_bank) {
                case 12: func_9980_b12(); break;
                case 2: func_9980_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x81E8:
            func_81E8_b12(); break;
        case 0x8616:
            func_8616_b12(); break;
        case 0xF9A5:
            func_F9A5(); break;
        case 0x8321:
            func_8321_b12(); break;
        case 0x82B4:
            func_82B4_b12(); break;
        case 0x8EC1:
            switch (g_current_bank) {
                case 12: func_8EC1_b12(); break;
                case 4: func_8EC1_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8501:
            switch (g_current_bank) {
                case 12: func_8501_b12(); break;
                case 2: func_8501_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x99F8:
            func_99F8_b12(); break;
        case 0x84ED:
            func_84ED_b12(); break;
        case 0x8482:
            func_8482_b12(); break;
        case 0x8471:
            switch (g_current_bank) {
                case 12: func_8471_b12(); break;
                case 4: func_8471_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x837C:
            switch (g_current_bank) {
                case 12: func_837C_b12(); break;
                case 6: func_837C_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x837E:
            switch (g_current_bank) {
                case 12: func_837E_b12(); break;
                case 0: func_837E_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8537:
            switch (g_current_bank) {
                case 12: func_8537_b12(); break;
                case 0: func_8537_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8574:
            switch (g_current_bank) {
                case 12: func_8574_b12(); break;
                case 14: func_8574_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x85A3:
            switch (g_current_bank) {
                case 12: func_85A3_b12(); break;
                case 11: func_85A3_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xF3E9:
            func_F3E9(); break;
        case 0x8704:
            switch (g_current_bank) {
                case 12: func_8704_b12(); break;
                case 6: func_8704_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x96E5:
            func_96E5_b12(); break;
        case 0xF434:
            func_F434(); break;
        case 0x8757:
            func_8757_b12(); break;
        case 0x96F1:
            func_96F1_b12(); break;
        case 0xF4FF:
            func_F4FF(); break;
        case 0x87C1:
            func_87C1_b12(); break;
        case 0x8216:
            func_8216_b12(); break;
        case 0xF29B:
            func_F29B(); break;
        case 0xDFFF:
            func_DFFF(); break;
        case 0x807F:
            func_807F_b14(); break;
        case 0x92FB:
            func_92FB_b1(); break;
        case 0x930E:
            func_930E_b1(); break;
        case 0x9D33:
            func_9D33_b1(); break;
        case 0xF6D3:
            func_F6D3(); break;
        case 0x9C76:
            func_9C76_b1(); break;
        case 0xFD34:
            func_FD34(); break;
        case 0x9DCF:
            switch (g_current_bank) {
                case 1: func_9DCF_b1(); break;
                case 4: func_9DCF_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xF5D6:
            func_F5D6(); break;
        case 0xDCBF:
            func_DCBF(); break;
        case 0xA7F0:
            func_A7F0_b12(); break;
        case 0xA9F1:
            func_A9F1_b12(); break;
        case 0xB3BD:
            func_B3BD_b1(); break;
        case 0x9750:
            func_9750_b12(); break;
        case 0x99A0:
            func_99A0_b12(); break;
        case 0xF528:
            func_F528(); break;
        case 0x90E2:
            func_90E2_b10(); break;
        case 0xA0C6:
            func_A0C6_b10(); break;
        case 0x9388:
            func_9388_b2(); break;
        case 0xFF43:
            func_FF43(); break;
        case 0x8543:
            func_8543_b14(); break;
        case 0x87AF:
            func_87AF_b12(); break;
        case 0x997C:
            func_997C_b12(); break;
        case 0x9962:
            func_9962_b12(); break;
        case 0xF299:
            func_F299(); break;
        case 0x8076:
            func_8076_b14(); break;
        case 0x929F:
            switch (g_current_bank) {
                case 15: func_D29F(); break;
                case 1: func_929F_b1(); break;
                case 14: func_929F_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9CCC:
            func_9CCC_b1(); break;
        case 0x9C6D:
            func_9C6D_b1(); break;
        case 0x90D4:
            func_90D4_b10(); break;
        case 0x88C3:
            func_88C3_b2(); break;
        case 0xFC70:
            func_FC70(); break;
        case 0x8999:
            switch (g_current_bank) {
                case 15: func_C999(); break;
                case 10: func_8999_b10(); break;
                case 14: func_8999_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x88A1:
            func_88A1_b2(); break;
        case 0xFC6E:
            func_FC6E(); break;
        case 0x8883:
            func_8883_b2(); break;
        case 0x9C05:
            func_9C05_b0(); break;
        case 0x8301:
            switch (g_current_bank) {
                case 0: func_8301_b0(); break;
                case 1: func_8301_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9D76:
            func_9D76_b0(); break;
        case 0x80DA:
            func_80DA_b0(); break;
        case 0xB3D7:
            func_B3D7_b0(); break;
        case 0xA436:
            func_A436_b0(); break;
        case 0x9B3D:
            switch (g_current_bank) {
                case 0: func_9B3D_b0(); break;
                case 2: func_9B3D_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9CD8:
            func_9CD8_b0(); break;
        case 0xB6D8:
            func_B6D8_b0(); break;
        case 0x9D73:
            func_9D73_b0(); break;
        case 0x850E:
            switch (g_current_bank) {
                case 0: func_850E_b0(); break;
                case 5: func_850E_b5(); break;
                case 12: func_850E_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA78D:
            func_A78D_b0(); break;
        case 0x9DD4:
            func_9DD4_b0(); break;
        case 0xB5D8:
            func_B5D8_b0(); break;
        case 0xB1D1:
            switch (g_current_bank) {
                case 15: func_F1D1(); break;
                case 0: func_B1D1_b0(); break;
                case 1: func_B1D1_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA9C5:
            func_A9C5_b0(); break;
        case 0xB60D:
            func_B60D_b0(); break;
        case 0x9D1F:
            func_9D1F_b0(); break;
        case 0xB322:
            func_B322_b0(); break;
        case 0x922A:
            func_922A_b0(); break;
        case 0x9936:
            func_9936_b0(); break;
        case 0xB0C4:
            func_B0C4_b0(); break;
        case 0xB1C4:
            switch (g_current_bank) {
                case 15: func_F1C4(); break;
                case 0: func_B1C4_b0(); break;
                case 1: func_B1C4_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x936D:
            switch (g_current_bank) {
                case 0: func_936D_b0(); break;
                case 1: func_936D_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x975D:
            func_975D_b0(); break;
        case 0xB2C3:
            func_B2C3_b0(); break;
        case 0x8CB3:
            func_8CB3_b0(); break;
        case 0xA38D:
            func_A38D_b0(); break;
        case 0xB1C2:
            switch (g_current_bank) {
                case 0: func_B1C2_b0(); break;
                case 1: func_B1C2_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA36D:
            func_A36D_b0(); break;
        case 0x87B2:
            func_87B2_b0(); break;
        case 0xB226:
            func_B226_b0(); break;
        case 0xAC15:
            func_AC15_b0(); break;
        case 0xB7F1:
            func_B7F1_b0(); break;
        case 0x970D:
            func_970D_b0(); break;
        case 0xBB31:
            func_BB31_b0(); break;
        case 0xB5B1:
            func_B5B1_b0(); break;
        case 0x972D:
            func_972D_b0(); break;
        case 0x930D:
            func_930D_b0(); break;
        case 0x978D:
            func_978D_b0(); break;
        case 0xACC2:
            func_ACC2_b0(); break;
        case 0x87C4:
            switch (g_current_bank) {
                case 0: func_87C4_b0(); break;
                case 2: func_87C4_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x985D:
            func_985D_b0(); break;
        case 0xB228:
            func_B228_b0(); break;
        case 0xB0F1:
            switch (g_current_bank) {
                case 15: func_F0F1(); break;
                case 0: func_B0F1_b0(); break;
                case 14: func_B0F1_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9B0D:
            switch (g_current_bank) {
                case 0: func_9B0D_b0(); break;
                case 2: func_9B0D_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA34D:
            func_A34D_b0(); break;
        case 0xACC5:
            func_ACC5_b0(); break;
        case 0x9DF1:
            func_9DF1_b0(); break;
        case 0x8373:
            func_8373_b0(); break;
        case 0xB212:
            func_B212_b0(); break;
        case 0x944D:
            func_944D_b0(); break;
        case 0x8F4D:
            func_8F4D_b0(); break;
        case 0x8731:
            switch (g_current_bank) {
                case 0: func_8731_b0(); break;
                case 11: func_8731_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8FAD:
            func_8FAD_b0(); break;
        case 0xB3CF:
            func_B3CF_b0(); break;
        case 0xBCB3:
            func_BCB3_b0(); break;
        case 0x943D:
            func_943D_b0(); break;
        case 0x85C2:
            switch (g_current_bank) {
                case 0: func_85C2_b0(); break;
                case 3: func_85C2_b3(); break;
                case 4: func_85C2_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9B7D:
            switch (g_current_bank) {
                case 0: func_9B7D_b0(); break;
                case 1: func_9B7D_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C07:
            switch (g_current_bank) {
                case 0: func_8C07_b0(); break;
                case 7: func_8C07_b7(); break;
                case 5: func_8C07_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8775:
            switch (g_current_bank) {
                case 0: func_8775_b0(); break;
                case 1: func_8775_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8F2D:
            func_8F2D_b0(); break;
        case 0xA15D:
            func_A15D_b0(); break;
        case 0x8CC8:
            func_8CC8_b0(); break;
        case 0x8B31:
            func_8B31_b0(); break;
        case 0x953D:
            func_953D_b0(); break;
        case 0x939D:
            func_939D_b0(); break;
        case 0xB1C7:
            switch (g_current_bank) {
                case 0: func_B1C7_b0(); break;
                case 14: func_B1C7_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA3C5:
            func_A3C5_b0(); break;
        case 0x94AD:
            func_94AD_b0(); break;
        case 0x916D:
            func_916D_b0(); break;
        case 0x95CD:
            func_95CD_b0(); break;
        case 0xB0C8:
            switch (g_current_bank) {
                case 15: func_F0C8(); break;
                case 0: func_B0C8_b0(); break;
                case 2: func_B0C8_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8127:
            func_8127_b0(); break;
        case 0xA03D:
            switch (g_current_bank) {
                case 0: func_A03D_b0(); break;
                case 5: func_A03D_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA202:
            switch (g_current_bank) {
                case 0: func_A202_b0(); break;
                case 14: func_A202_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9F7D:
            switch (g_current_bank) {
                case 15: func_DF7D(); break;
                case 0: func_9F7D_b0(); break;
                case 1: func_9F7D_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x937D:
            func_937D_b0(); break;
        case 0x8D35:
            func_8D35_b0(); break;
        case 0x8314:
            func_8314_b0(); break;
        case 0x8C14:
            func_8C14_b0(); break;
        case 0x9D7D:
            func_9D7D_b0(); break;
        case 0x8CF2:
            switch (g_current_bank) {
                case 0: func_8CF2_b0(); break;
                case 2: func_8CF2_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9F2D:
            func_9F2D_b0(); break;
        case 0x88F2:
            func_88F2_b0(); break;
        case 0x8EAD:
            func_8EAD_b0(); break;
        case 0xA00D:
            func_A00D_b0(); break;
        case 0xA7C5:
            func_A7C5_b0(); break;
        case 0xA1DD:
            func_A1DD_b0(); break;
        case 0x870E:
            func_870E_b0(); break;
        case 0xB4D3:
            func_B4D3_b0(); break;
        case 0xB0C1:
            func_B0C1_b0(); break;
        case 0x9CB1:
            switch (g_current_bank) {
                case 15: func_DCB1(); break;
                case 0: func_9CB1_b0(); break;
                case 2: func_9CB1_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9C01:
            switch (g_current_bank) {
                case 0: func_9C01_b0(); break;
                case 4: func_9C01_b4(); break;
                case 6: func_9C01_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x979D:
            func_979D_b0(); break;
        case 0xB299:
            func_B299_b0(); break;
        case 0x8D8D:
            switch (g_current_bank) {
                case 0: func_8D8D_b0(); break;
                case 8: func_8D8D_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x950D:
            switch (g_current_bank) {
                case 0: func_950D_b0(); break;
                case 1: func_950D_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB7B4:
            func_B7B4_b0(); break;
        case 0x964D:
            func_964D_b0(); break;
        case 0x9A5D:
            func_9A5D_b0(); break;
        case 0x8C28:
            func_8C28_b0(); break;
        case 0xA1CA:
            func_A1CA_b0(); break;
        case 0xB2CE:
            func_B2CE_b0(); break;
        case 0xA2CE:
            func_A2CE_b0(); break;
        case 0xA33D:
            func_A33D_b0(); break;
        case 0x829D:
            func_829D_b0(); break;
        case 0x9C13:
            func_9C13_b0(); break;
        case 0xA3BD:
            func_A3BD_b0(); break;
        case 0xABBE:
            func_ABBE_b0(); break;
        case 0xAD78:
            func_AD78_b0(); break;
        case 0xB6DF:
            func_B6DF_b0(); break;
        case 0x994E:
            func_994E_b0(); break;
        case 0xA078:
            func_A078_b0(); break;
        case 0xB3FD:
            func_B3FD_b0(); break;
        case 0xADE0:
            func_ADE0_b0(); break;
        case 0xB336:
            func_B336_b0(); break;
        case 0xBDF8:
            switch (g_current_bank) {
                case 0: func_BDF8_b0(); break;
                case 2: func_BDF8_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x830E:
            func_830E_b0(); break;
        case 0xBF2E:
            func_BF2E_b0(); break;
        case 0xBACE:
            switch (g_current_bank) {
                case 0: func_BACE_b0(); break;
                case 14: func_BACE_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB5DB:
            switch (g_current_bank) {
                case 0: func_B5DB_b0(); break;
                case 1: func_B5DB_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8737:
            switch (g_current_bank) {
                case 15: func_C737(); break;
                case 0: func_8737_b0(); break;
                case 12: func_8737_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAC77:
            func_AC77_b0(); break;
        case 0xBC72:
            switch (g_current_bank) {
                case 0: func_BC72_b0(); break;
                case 1: func_BC72_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9336:
            func_9336_b0(); break;
        case 0x9DB6:
            func_9DB6_b0(); break;
        case 0xBD72:
            func_BD72_b0(); break;
        case 0xB54F:
            switch (g_current_bank) {
                case 0: func_B54F_b0(); break;
                case 4: func_B54F_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBB4E:
            func_BB4E_b0(); break;
        case 0x8B1D:
            func_8B1D_b0(); break;
        case 0xB12D:
            func_B12D_b0(); break;
        case 0xB05D:
            func_B05D_b0(); break;
        case 0xB22D:
            switch (g_current_bank) {
                case 0: func_B22D_b0(); break;
                case 6: func_B22D_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAB77:
            func_AB77_b0(); break;
        case 0xB55E:
            func_B55E_b0(); break;
        case 0xAABE:
            switch (g_current_bank) {
                case 0: func_AABE_b0(); break;
                case 4: func_AABE_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBBCE:
            func_BBCE_b0(); break;
        case 0x9F4E:
            func_9F4E_b0(); break;
        case 0xA3DE:
            func_A3DE_b0(); break;
        case 0x9CDE:
            switch (g_current_bank) {
                case 0: func_9CDE_b0(); break;
                case 10: func_9CDE_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBB1E:
            func_BB1E_b0(); break;
        case 0xB31D:
            func_B31D_b0(); break;
        case 0xA99E:
            func_A99E_b0(); break;
        case 0xB2D0:
            func_B2D0_b0(); break;
        case 0xB360:
            switch (g_current_bank) {
                case 0: func_B360_b0(); break;
                case 6: func_B360_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xABD0:
            func_ABD0_b0(); break;
        case 0x9C37:
            func_9C37_b0(); break;
        case 0xB69D:
            func_B69D_b0(); break;
        case 0xA68E:
            func_A68E_b0(); break;
        case 0xA5AE:
            switch (g_current_bank) {
                case 0: func_A5AE_b0(); break;
                case 3: func_A5AE_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB79D:
            func_B79D_b0(); break;
        case 0xB660:
            func_B660_b0(); break;
        case 0xB71D:
            func_B71D_b0(); break;
        case 0xB7D7:
            func_B7D7_b0(); break;
        case 0x805E:
            func_805E_b0(); break;
        case 0xB7E0:
            switch (g_current_bank) {
                case 15: func_F7E0(); break;
                case 0: func_B7E0_b0(); break;
                case 8: func_B7E0_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x875E:
            func_875E_b0(); break;
        case 0xBB9E:
            switch (g_current_bank) {
                case 0: func_BB9E_b0(); break;
                case 1: func_BB9E_b1(); break;
                case 6: func_BB9E_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB14D:
            func_B14D_b0(); break;
        case 0x9DDF:
            func_9DDF_b0(); break;
        case 0xB95E:
            switch (g_current_bank) {
                case 0: func_B95E_b0(); break;
                case 2: func_B95E_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x97F6:
            func_97F6_b0(); break;
        case 0x9376:
            func_9376_b0(); break;
        case 0xB15D:
            func_B15D_b0(); break;
        case 0xBD38:
            func_BD38_b0(); break;
        case 0x9EDE:
            func_9EDE_b0(); break;
        case 0x9736:
            func_9736_b0(); break;
        case 0xAFDE:
            func_AFDE_b0(); break;
        case 0x894D:
            switch (g_current_bank) {
                case 15: func_C94D(); break;
                case 0: func_894D_b0(); break;
                case 11: func_894D_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAF2E:
            func_AF2E_b0(); break;
        case 0xBF3E:
            func_BF3E_b0(); break;
        case 0xB4D0:
            func_B4D0_b0(); break;
        case 0x9B31:
            func_9B31_b0(); break;
        case 0x9CC7:
            switch (g_current_bank) {
                case 0: func_9CC7_b0(); break;
                case 2: func_9CC7_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB25D:
            switch (g_current_bank) {
                case 0: func_B25D_b0(); break;
                case 6: func_B25D_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB245:
            func_B245_b0(); break;
        case 0xAB9D:
            func_AB9D_b0(); break;
        case 0xAD37:
            func_AD37_b0(); break;
        case 0x93CE:
            func_93CE_b0(); break;
        case 0xB5CC:
            func_B5CC_b0(); break;
        case 0xA574:
            switch (g_current_bank) {
                case 0: func_A574_b0(); break;
                case 14: func_A574_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB574:
            func_B574_b0(); break;
        case 0x8BDD:
            func_8BDD_b0(); break;
        case 0xB5C6:
            func_B5C6_b0(); break;
        case 0x8FED:
            switch (g_current_bank) {
                case 0: func_8FED_b0(); break;
                case 10: func_8FED_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB1CB:
            func_B1CB_b0(); break;
        case 0xB1D9:
            switch (g_current_bank) {
                case 0: func_B1D9_b0(); break;
                case 4: func_B1D9_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x90D9:
            switch (g_current_bank) {
                case 15: func_D0D9(); break;
                case 0: func_90D9_b0(); break;
                case 10: func_90D9_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA331:
            func_A331_b0(); break;
        case 0xA7D1:
            func_A7D1_b0(); break;
        case 0x9142:
            func_9142_b0(); break;
        case 0xBF00:
            switch (g_current_bank) {
                case 15: func_FF00(); break;
                case 0: func_BF00_b0(); break;
                case 4: func_BF00_b4(); break;
                case 5: func_BF00_b5(); break;
                case 6: func_BF00_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x850B:
            func_850B_b1(); break;
        case 0xB811:
            func_B811_b1(); break;
        case 0x871A:
            func_871A_b1(); break;
        case 0xB0C2:
            switch (g_current_bank) {
                case 15: func_F0C2(); break;
                case 1: func_B0C2_b1(); break;
                case 2: func_B0C2_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C79:
            func_8C79_b1(); break;
        case 0xB119:
            switch (g_current_bank) {
                case 1: func_B119_b1(); break;
                case 4: func_B119_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8AB1:
            func_8AB1_b1(); break;
        case 0x83C3:
            switch (g_current_bank) {
                case 1: func_83C3_b1(); break;
                case 0: func_83C3_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB1C9:
            func_B1C9_b1(); break;
        case 0x90F3:
            switch (g_current_bank) {
                case 1: func_90F3_b1(); break;
                case 5: func_90F3_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB0CB:
            func_B0CB_b1(); break;
        case 0xA3B1:
            func_A3B1_b1(); break;
        case 0x902D:
            switch (g_current_bank) {
                case 1: func_902D_b1(); break;
                case 5: func_902D_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x80C3:
            func_80C3_b1(); break;
        case 0xB2C2:
            func_B2C2_b1(); break;
        case 0xACC4:
            func_ACC4_b1(); break;
        case 0x9CF3:
            func_9CF3_b1(); break;
        case 0xB216:
            func_B216_b1(); break;
        case 0x889D:
            switch (g_current_bank) {
                case 1: func_889D_b1(); break;
                case 6: func_889D_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBC32:
            func_BC32_b1(); break;
        case 0xAAAB:
            switch (g_current_bank) {
                case 1: func_AAAB_b1(); break;
                case 7: func_AAAB_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9DF6:
            func_9DF6_b1(); break;
        case 0xABAB:
            func_ABAB_b1(); break;
        case 0xB2D1:
            func_B2D1_b1(); break;
        case 0x87F1:
            func_87F1_b1(); break;
        case 0xB736:
            func_B736_b1(); break;
        case 0xAF0D:
            func_AF0D_b1(); break;
        case 0x8DE1:
            func_8DE1_b1(); break;
        case 0xB3D1:
            func_B3D1_b1(); break;
        case 0x9D74:
            func_9D74_b1(); break;
        case 0xB011:
            func_B011_b1(); break;
        case 0x94F4:
            func_94F4_b1(); break;
        case 0xBBBD:
            func_BBBD_b1(); break;
        case 0xAF2D:
            func_AF2D_b1(); break;
        case 0xBDB6:
            func_BDB6_b1(); break;
        case 0x9B8E:
            func_9B8E_b1(); break;
        case 0xB6DB:
            func_B6DB_b1(); break;
        case 0xAA2B:
            func_AA2B_b1(); break;
        case 0xB44E:
            func_B44E_b1(); break;
        case 0xACF7:
            func_ACF7_b1(); break;
        case 0xAA3B:
            func_AA3B_b1(); break;
        case 0xBF8D:
            func_BF8D_b1(); break;
        case 0x9077:
            func_9077_b1(); break;
        case 0xBD37:
            func_BD37_b1(); break;
        case 0x9D59:
            func_9D59_b1(); break;
        case 0x8DF1:
            func_8DF1_b1(); break;
        case 0xBCB2:
            func_BCB2_b1(); break;
        case 0xA077:
            switch (g_current_bank) {
                case 1: func_A077_b1(); break;
                case 14: func_A077_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAABB:
            func_AABB_b1(); break;
        case 0xB04D:
            func_B04D_b1(); break;
        case 0xAC0E:
            func_AC0E_b1(); break;
        case 0xAB5D:
            func_AB5D_b1(); break;
        case 0x802C:
            func_802C_b1(); break;
        case 0x83ED:
            func_83ED_b1(); break;
        case 0xB4D1:
            func_B4D1_b1(); break;
        case 0x8D71:
            switch (g_current_bank) {
                case 1: func_8D71_b1(); break;
                case 5: func_8D71_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9D36:
            func_9D36_b1(); break;
        case 0xAA23:
            func_AA23_b1(); break;
        case 0xBCB6:
            func_BCB6_b1(); break;
        case 0xB451:
            func_B451_b1(); break;
        case 0x976D:
            func_976D_b1(); break;
        case 0xB143:
            func_B143_b1(); break;
        case 0x8DC9:
            func_8DC9_b1(); break;
        case 0xAA73:
            func_AA73_b1(); break;
        case 0xBB6D:
            func_BB6D_b1(); break;
        case 0xACF1:
            func_ACF1_b1(); break;
        case 0xAC32:
            func_AC32_b1(); break;
        case 0x911E:
            func_911E_b1(); break;
        case 0x9F1D:
            func_9F1D_b1(); break;
        case 0x9CCB:
            switch (g_current_bank) {
                case 15: func_DCCB(); break;
                case 1: func_9CCB_b1(); break;
                case 2: func_9CCB_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB776:
            switch (g_current_bank) {
                case 1: func_B776_b1(); break;
                case 0: func_B776_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x937E:
            func_937E_b1(); break;
        case 0xA8AB:
            switch (g_current_bank) {
                case 1: func_A8AB_b1(); break;
                case 14: func_A8AB_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x835D:
            switch (g_current_bank) {
                case 1: func_835D_b1(); break;
                case 2: func_835D_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAF6D:
            func_AF6D_b1(); break;
        case 0xB5D6:
            func_B5D6_b1(); break;
        case 0xA554:
            func_A554_b1(); break;
        case 0x80CE:
            func_80CE_b1(); break;
        case 0xB009:
            func_B009_b1(); break;
        case 0x8BF6:
            func_8BF6_b1(); break;
        case 0x9D77:
            func_9D77_b1(); break;
        case 0xB6E0:
            switch (g_current_bank) {
                case 1: func_B6E0_b1(); break;
                case 2: func_B6E0_b2(); break;
                case 3: func_B6E0_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBD78:
            func_BD78_b1(); break;
        case 0x8078:
            func_8078_b1(); break;
        case 0x9DDC:
            func_9DDC_b1(); break;
        case 0xA39E:
            func_A39E_b1(); break;
        case 0x910E:
            func_910E_b1(); break;
        case 0xB3DC:
            func_B3DC_b1(); break;
        case 0x8D76:
            func_8D76_b1(); break;
        case 0x9037:
            switch (g_current_bank) {
                case 1: func_9037_b1(); break;
                case 5: func_9037_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9CDD:
            switch (g_current_bank) {
                case 1: func_9CDD_b1(); break;
                case 4: func_9CDD_b4(); break;
                case 6: func_9CDD_b6(); break;
                case 10: func_9CDD_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x81CE:
            switch (g_current_bank) {
                case 1: func_81CE_b1(); break;
                case 3: func_81CE_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA9DB:
            func_A9DB_b1(); break;
        case 0x81ED:
            func_81ED_b1(); break;
        case 0xB5B6:
            func_B5B6_b1(); break;
        case 0xACAB:
            func_ACAB_b1(); break;
        case 0x81AD:
            func_81AD_b1(); break;
        case 0x9DB7:
            func_9DB7_b1(); break;
        case 0xB74F:
            func_B74F_b1(); break;
        case 0x9177:
            func_9177_b1(); break;
        case 0xAA6B:
            func_AA6B_b1(); break;
        case 0x8CCE:
            func_8CCE_b1(); break;
        case 0xB3B7:
            switch (g_current_bank) {
                case 1: func_B3B7_b1(); break;
                case 3: func_B3B7_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB51E:
            func_B51E_b1(); break;
        case 0x8A31:
            func_8A31_b1(); break;
        case 0xB372:
            func_B372_b1(); break;
        case 0xA3D4:
            switch (g_current_bank) {
                case 1: func_A3D4_b1(); break;
                case 10: func_A3D4_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C15:
            func_8C15_b1(); break;
        case 0xA7F2:
            switch (g_current_bank) {
                case 1: func_A7F2_b1(); break;
                case 2: func_A7F2_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB7EE:
            func_B7EE_b1(); break;
        case 0x8278:
            func_8278_b1(); break;
        case 0xACFB:
            func_ACFB_b1(); break;
        case 0xB9BE:
            func_B9BE_b1(); break;
        case 0xB79E:
            func_B79E_b1(); break;
        case 0xABCE:
            func_ABCE_b1(); break;
        case 0xAC3D:
            func_AC3D_b1(); break;
        case 0xB2CA:
            switch (g_current_bank) {
                case 1: func_B2CA_b1(); break;
                case 2: func_B2CA_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBD0D:
            switch (g_current_bank) {
                case 1: func_BD0D_b1(); break;
                case 14: func_BD0D_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9CF1:
            func_9CF1_b1(); break;
        case 0xB3CC:
            func_B3CC_b1(); break;
        case 0xA5B4:
            func_A5B4_b1(); break;
        case 0x9071:
            func_9071_b1(); break;
        case 0xA174:
            func_A174_b1(); break;
        case 0x83F4:
            func_83F4_b1(); break;
        case 0x9771:
            func_9771_b1(); break;
        case 0x9CC9:
            switch (g_current_bank) {
                case 1: func_9CC9_b1(); break;
                case 6: func_9CC9_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8CCA:
            func_8CCA_b1(); break;
        case 0xB6CD:
            func_B6CD_b1(); break;
        case 0x8F8D:
            func_8F8D_b1(); break;
        case 0x97DD:
            switch (g_current_bank) {
                case 1: func_97DD_b1(); break;
                case 8: func_97DD_b8(); break;
                case 2: func_97DD_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x80CA:
            switch (g_current_bank) {
                case 1: func_80CA_b1(); break;
                case 12: func_80CA_b12(); break;
                case 14: func_80CA_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB973:
            func_B973_b1(); break;
        case 0xAD4D:
            switch (g_current_bank) {
                case 1: func_AD4D_b1(); break;
                case 14: func_AD4D_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8B9D:
            func_8B9D_b1(); break;
        case 0xB3C8:
            func_B3C8_b1(); break;
        case 0xAF4D:
            func_AF4D_b1(); break;
        case 0xB5BD:
            func_B5BD_b1(); break;
        case 0x919D:
            func_919D_b1(); break;
        case 0xAD74:
            func_AD74_b1(); break;
        case 0xB573:
            func_B573_b1(); break;
        case 0xA734:
            func_A734_b1(); break;
        case 0x83B5:
            func_83B5_b1(); break;
        case 0x97CF:
            func_97CF_b1(); break;
        case 0x94CF:
            func_94CF_b1(); break;
        case 0xB32E:
            func_B32E_b1(); break;
        case 0x83D0:
            func_83D0_b1(); break;
        case 0x991D:
            func_991D_b1(); break;
        case 0x97ED:
            func_97ED_b1(); break;
        case 0x8A33:
            func_8A33_b1(); break;
        case 0xAC27:
            func_AC27_b1(); break;
        case 0xAC2C:
            func_AC2C_b1(); break;
        case 0x958D:
            func_958D_b1(); break;
        case 0xABCA:
            func_ABCA_b1(); break;
        case 0xA334:
            func_A334_b1(); break;
        case 0x984D:
            func_984D_b1(); break;
        case 0xB342:
            func_B342_b1(); break;
        case 0x90CF:
            func_90CF_b1(); break;
        case 0xA4CA:
            func_A4CA_b1(); break;
        case 0x8C74:
            func_8C74_b1(); break;
        case 0x9A8D:
            func_9A8D_b1(); break;
        case 0x8900:
            switch (g_current_bank) {
                case 15: func_C900(); break;
                case 1: func_8900_b1(); break;
                case 4: func_8900_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB0B2:
            switch (g_current_bank) {
                case 2: func_B0B2_b2(); break;
                case 4: func_B0B2_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB1C6:
            func_B1C6_b2(); break;
        case 0xB1C8:
            switch (g_current_bank) {
                case 2: func_B1C8_b2(); break;
                case 3: func_B1C8_b3(); break;
                case 14: func_B1C8_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x83C7:
            func_83C7_b2(); break;
        case 0x8CC6:
            switch (g_current_bank) {
                case 2: func_8CC6_b2(); break;
                case 1: func_8CC6_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8B2D:
            func_8B2D_b2(); break;
        case 0x836D:
            func_836D_b2(); break;
        case 0x87C6:
            func_87C6_b2(); break;
        case 0x9CC1:
            func_9CC1_b2(); break;
        case 0x8C0E:
            func_8C0E_b2(); break;
        case 0x9C72:
            func_9C72_b2(); break;
        case 0x810D:
            func_810D_b2(); break;
        case 0xA3C4:
            func_A3C4_b2(); break;
        case 0x85C9:
            switch (g_current_bank) {
                case 2: func_85C9_b2(); break;
                case 11: func_85C9_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA072:
            func_A072_b2(); break;
        case 0x850D:
            func_850D_b2(); break;
        case 0x873D:
            func_873D_b2(); break;
        case 0x815D:
            func_815D_b2(); break;
        case 0xB4CA:
            func_B4CA_b2(); break;
        case 0x95C7:
            func_95C7_b2(); break;
        case 0x952D:
            func_952D_b2(); break;
        case 0xA94D:
            func_A94D_b2(); break;
        case 0xA1B2:
            func_A1B2_b2(); break;
        case 0xB0CF:
            func_B0CF_b2(); break;
        case 0x8C32:
            switch (g_current_bank) {
                case 2: func_8C32_b2(); break;
                case 5: func_8C32_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C71:
            func_8C71_b2(); break;
        case 0x83C2:
            func_83C2_b2(); break;
        case 0x9732:
            func_9732_b2(); break;
        case 0xA171:
            func_A171_b2(); break;
        case 0x90C1:
            switch (g_current_bank) {
                case 2: func_90C1_b2(); break;
                case 6: func_90C1_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x93F1:
            func_93F1_b2(); break;
        case 0x872D:
            func_872D_b2(); break;
        case 0xA531:
            switch (g_current_bank) {
                case 2: func_A531_b2(); break;
                case 14: func_A531_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8DB5:
            func_8DB5_b2(); break;
        case 0x9018:
            func_9018_b2(); break;
        case 0xBD76:
            func_BD76_b2(); break;
        case 0xB6DA:
            func_B6DA_b2(); break;
        case 0x8C44:
            func_8C44_b2(); break;
        case 0x8375:
            func_8375_b2(); break;
        case 0x8D4C:
            func_8D4C_b2(); break;
        case 0xB6E7:
            func_B6E7_b2(); break;
        case 0x871E:
            switch (g_current_bank) {
                case 2: func_871E_b2(); break;
                case 6: func_871E_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9F50:
            func_9F50_b2(); break;
        case 0xB452:
            func_B452_b2(); break;
        case 0xB8DF:
            func_B8DF_b2(); break;
        case 0x80F2:
            func_80F2_b2(); break;
        case 0x8A20:
            func_8A20_b2(); break;
        case 0x8A29:
            switch (g_current_bank) {
                case 2: func_8A29_b2(); break;
                case 11: func_8A29_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C34:
            func_8C34_b2(); break;
        case 0x895D:
            func_895D_b2(); break;
        case 0x85DD:
            func_85DD_b2(); break;
        case 0x83C9:
            func_83C9_b2(); break;
        case 0x8B5D:
            func_8B5D_b2(); break;
        case 0xA7B3:
            func_A7B3_b2(); break;
        case 0x95C2:
            func_95C2_b2(); break;
        case 0x8CB4:
            switch (g_current_bank) {
                case 2: func_8CB4_b2(); break;
                case 5: func_8CB4_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x83B2:
            func_83B2_b2(); break;
        case 0x890D:
            func_890D_b2(); break;
        case 0xB3C7:
            func_B3C7_b2(); break;
        case 0xB2CF:
            func_B2CF_b2(); break;
        case 0xA99D:
            func_A99D_b2(); break;
        case 0xB2C8:
            func_B2C8_b2(); break;
        case 0x9433:
            func_9433_b2(); break;
        case 0xA1FD:
            func_A1FD_b2(); break;
        case 0x97CC:
            func_97CC_b2(); break;
        case 0xACF4:
            func_ACF4_b2(); break;
        case 0x99BD:
            switch (g_current_bank) {
                case 2: func_99BD_b2(); break;
                case 3: func_99BD_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x97C8:
            func_97C8_b2(); break;
        case 0x8F0D:
            func_8F0D_b2(); break;
        case 0xB2C6:
            switch (g_current_bank) {
                case 2: func_B2C6_b2(); break;
                case 10: func_B2C6_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA572:
            func_A572_b2(); break;
        case 0xA12D:
            switch (g_current_bank) {
                case 2: func_A12D_b2(); break;
                case 14: func_A12D_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA773:
            func_A773_b2(); break;
        case 0x9901:
            switch (g_current_bank) {
                case 2: func_9901_b2(); break;
                case 6: func_9901_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x80FE:
            func_80FE_b2(); break;
        case 0xA601:
            func_A601_b2(); break;
        case 0x8A01:
            func_8A01_b2(); break;
        case 0x9801:
            switch (g_current_bank) {
                case 2: func_9801_b2(); break;
                case 5: func_9801_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x80FC:
            func_80FC_b2(); break;
        case 0xA201:
            func_A201_b2(); break;
        case 0xBA00:
            switch (g_current_bank) {
                case 2: func_BA00_b2(); break;
                case 4: func_BA00_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9F00:
            switch (g_current_bank) {
                case 2: func_9F00_b2(); break;
                case 3: func_9F00_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA500:
            func_A500_b2(); break;
        case 0xB7FC:
            func_B7FC_b2(); break;
        case 0xB7FF:
            func_B7FF_b2(); break;
        case 0xBDA0:
            func_BDA0_b2(); break;
        case 0x9000:
            func_9000_b2(); break;
        case 0x85E0:
            switch (g_current_bank) {
                case 2: func_85E0_b2(); break;
                case 14: func_85E0_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB600:
            switch (g_current_bank) {
                case 2: func_B600_b2(); break;
                case 3: func_B600_b3(); break;
                case 7: func_B600_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C80:
            func_8C80_b2(); break;
        case 0xB580:
            func_B580_b2(); break;
        case 0xB500:
            func_B500_b2(); break;
        case 0x9100:
            func_9100_b2(); break;
        case 0xB5C0:
            func_B5C0_b2(); break;
        case 0xB5DF:
            func_B5DF_b2(); break;
        case 0xBDE0:
            func_BDE0_b2(); break;
        case 0xB700:
            switch (g_current_bank) {
                case 2: func_B700_b2(); break;
                case 7: func_B700_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA700:
            switch (g_current_bank) {
                case 2: func_A700_b2(); break;
                case 5: func_A700_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9DF8:
            func_9DF8_b2(); break;
        case 0xBF80:
            switch (g_current_bank) {
                case 2: func_BF80_b2(); break;
                case 4: func_BF80_b4(); break;
                case 7: func_BF80_b7(); break;
                case 8: func_BF80_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB9F8:
            switch (g_current_bank) {
                case 2: func_B9F8_b2(); break;
                case 5: func_B9F8_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB1F0:
            switch (g_current_bank) {
                case 15: func_F1F0(); break;
                case 2: func_B1F0_b2(); break;
                case 3: func_B1F0_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8EF0:
            func_8EF0_b2(); break;
        case 0xBE80:
            switch (g_current_bank) {
                case 2: func_BE80_b2(); break;
                case 7: func_BE80_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9BC0:
            func_9BC0_b2(); break;
        case 0xB1B8:
            func_B1B8_b2(); break;
        case 0x80EA:
            func_80EA_b2(); break;
        case 0xBB00:
            switch (g_current_bank) {
                case 2: func_BB00_b2(); break;
                case 5: func_BB00_b5(); break;
                case 8: func_BB00_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBEC0:
            switch (g_current_bank) {
                case 2: func_BEC0_b2(); break;
                case 3: func_BEC0_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8BFD:
            switch (g_current_bank) {
                case 2: func_8BFD_b2(); break;
                case 6: func_8BFD_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBBFF:
            func_BBFF_b2(); break;
        case 0xBAFC:
            func_BAFC_b2(); break;
        case 0x9978:
            func_9978_b2(); break;
        case 0xAC84:
            func_AC84_b3(); break;
        case 0xA684:
            func_A684_b3(); break;
        case 0x8394:
            func_8394_b3(); break;
        case 0x8384:
            switch (g_current_bank) {
                case 3: func_8384_b3(); break;
                case 12: func_8384_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8D96:
            func_8D96_b3(); break;
        case 0xB4B7:
            func_B4B7_b3(); break;
        case 0x93DA:
            func_93DA_b3(); break;
        case 0x8695:
            switch (g_current_bank) {
                case 3: func_8695_b3(); break;
                case 4: func_8695_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAF84:
            func_AF84_b3(); break;
        case 0x83EC:
            func_83EC_b3(); break;
        case 0x93D2:
            func_93D2_b3(); break;
        case 0xABAC:
            func_ABAC_b3(); break;
        case 0x9486:
            func_9486_b3(); break;
        case 0xB8A8:
            func_B8A8_b3(); break;
        case 0x838E:
            func_838E_b3(); break;
        case 0x9592:
            func_9592_b3(); break;
        case 0x9FA5:
            func_9FA5_b3(); break;
        case 0xB7B0:
            switch (g_current_bank) {
                case 3: func_B7B0_b3(); break;
                case 8: func_B7B0_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x94CC:
            func_94CC_b3(); break;
        case 0x9FBB:
            func_9FBB_b3(); break;
        case 0xAB84:
            func_AB84_b3(); break;
        case 0xA0D3:
            func_A0D3_b3(); break;
        case 0xA696:
            func_A696_b3(); break;
        case 0x9590:
            func_9590_b3(); break;
        case 0x8795:
            func_8795_b3(); break;
        case 0xBD88:
            func_BD88_b3(); break;
        case 0x9395:
            func_9395_b3(); break;
        case 0x83FC:
            func_83FC_b3(); break;
        case 0xBF95:
            func_BF95_b3(); break;
        case 0x87CE:
            func_87CE_b3(); break;
        case 0xA7A6:
            func_A7A6_b3(); break;
        case 0xB3A8:
            func_B3A8_b3(); break;
        case 0xA4D4:
            func_A4D4_b3(); break;
        case 0x9D04:
            switch (g_current_bank) {
                case 15: func_DD04(); break;
                case 3: func_9D04_b3(); break;
                case 14: func_9D04_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9A07:
            func_9A07_b3(); break;
        case 0xA200:
            func_A200_b3(); break;
        case 0x8001:
            switch (g_current_bank) {
                case 3: func_8001_b3(); break;
                case 4: func_8001_b4(); break;
                case 6: func_8001_b6(); break;
                case 7: func_8001_b7(); break;
                case 8: func_8001_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8BA6:
            func_8BA6_b3(); break;
        case 0x9195:
            func_9195_b3(); break;
        case 0x8184:
            switch (g_current_bank) {
                case 3: func_8184_b3(); break;
                case 4: func_8184_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8983:
            func_8983_b3(); break;
        case 0x8D86:
            switch (g_current_bank) {
                case 3: func_8D86_b3(); break;
                case 4: func_8D86_b4(); break;
                case 5: func_8D86_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA48C:
            func_A48C_b3(); break;
        case 0x8596:
            func_8596_b3(); break;
        case 0x8E86:
            func_8E86_b3(); break;
        case 0xA996:
            func_A996_b3(); break;
        case 0x9598:
            func_9598_b3(); break;
        case 0x9DAA:
            func_9DAA_b3(); break;
        case 0x81A5:
            func_81A5_b3(); break;
        case 0xA79C:
            func_A79C_b3(); break;
        case 0x859E:
            switch (g_current_bank) {
                case 15: func_C59E(); break;
                case 3: func_859E_b3(); break;
                case 12: func_859E_b12(); break;
                case 2: func_859E_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB5C7:
            switch (g_current_bank) {
                case 3: func_B5C7_b3(); break;
                case 1: func_B5C7_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9B82:
            func_9B82_b3(); break;
        case 0xA0DC:
            switch (g_current_bank) {
                case 3: func_A0DC_b3(); break;
                case 6: func_A0DC_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB0FA:
            func_B0FA_b3(); break;
        case 0x8198:
            func_8198_b3(); break;
        case 0x8AB2:
            func_8AB2_b3(); break;
        case 0xA58C:
            func_A58C_b3(); break;
        case 0x8F98:
            func_8F98_b3(); break;
        case 0x8C94:
            func_8C94_b3(); break;
        case 0xAAA4:
            func_AAA4_b3(); break;
        case 0xB1F7:
            func_B1F7_b3(); break;
        case 0x85A2:
            func_85A2_b3(); break;
        case 0x98C6:
            func_98C6_b3(); break;
        case 0x9BC2:
            func_9BC2_b3(); break;
        case 0x9B9C:
            func_9B9C_b3(); break;
        case 0x9BD4:
            func_9BD4_b3(); break;
        case 0x9CA2:
            func_9CA2_b3(); break;
        case 0x8FDD:
            switch (g_current_bank) {
                case 15: func_CFDD(); break;
                case 3: func_8FDD_b3(); break;
                case 1: func_8FDD_b1(); break;
                case 2: func_8FDD_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB1B2:
            switch (g_current_bank) {
                case 3: func_B1B2_b3(); break;
                case 4: func_B1B2_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8B98:
            func_8B98_b3(); break;
        case 0xB498:
            func_B498_b3(); break;
        case 0x8789:
            func_8789_b3(); break;
        case 0x9D9C:
            func_9D9C_b3(); break;
        case 0x81EE:
            switch (g_current_bank) {
                case 3: func_81EE_b3(); break;
                case 5: func_81EE_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x81E3:
            func_81E3_b3(); break;
        case 0x81A3:
            func_81A3_b3(); break;
        case 0xB5D7:
            func_B5D7_b3(); break;
        case 0xB5A0:
            func_B5A0_b3(); break;
        case 0x9594:
            func_9594_b3(); break;
        case 0x828D:
            func_828D_b3(); break;
        case 0x9697:
            func_9697_b3(); break;
        case 0xB187:
            func_B187_b3(); break;
        case 0x8699:
            func_8699_b3(); break;
        case 0xB6C0:
            func_B6C0_b3(); break;
        case 0x82E5:
            func_82E5_b3(); break;
        case 0x8284:
            switch (g_current_bank) {
                case 3: func_8284_b3(); break;
                case 12: func_8284_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBBB8:
            func_BBB8_b3(); break;
        case 0x8BB2:
            func_8BB2_b3(); break;
        case 0xA90C:
            switch (g_current_bank) {
                case 3: func_A90C_b3(); break;
                case 5: func_A90C_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8281:
            func_8281_b3(); break;
        case 0x958B:
            func_958B_b3(); break;
        case 0xB884:
            switch (g_current_bank) {
                case 3: func_B884_b3(); break;
                case 8: func_B884_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x86B9:
            func_86B9_b3(); break;
        case 0x8386:
            switch (g_current_bank) {
                case 3: func_8386_b3(); break;
                case 11: func_8386_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9800:
            func_9800_b3(); break;
        case 0xBA82:
            func_BA82_b3(); break;
        case 0x82A6:
            func_82A6_b3(); break;
        case 0x8B83:
            switch (g_current_bank) {
                case 3: func_8B83_b3(); break;
                case 14: func_8B83_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8685:
            func_8685_b3(); break;
        case 0x80B3:
            func_80B3_b3(); break;
        case 0x84F9:
            func_84F9_b3(); break;
        case 0xBFFA:
            func_BFFA_b3(); break;
        case 0xBFC0:
            switch (g_current_bank) {
                case 3: func_BFC0_b3(); break;
                case 4: func_BFC0_b4(); break;
                case 7: func_BFC0_b7(); break;
                case 8: func_BFC0_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8DC0:
            switch (g_current_bank) {
                case 3: func_8DC0_b3(); break;
                case 5: func_8DC0_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x81D2:
            func_81D2_b3(); break;
        case 0xB1D7:
            func_B1D7_b3(); break;
        case 0xB2D7:
            func_B2D7_b3(); break;
        case 0x9DCC:
            switch (g_current_bank) {
                case 3: func_9DCC_b3(); break;
                case 14: func_9DCC_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x99AF:
            func_99AF_b3(); break;
        case 0x829A:
            func_829A_b3(); break;
        case 0x8BFA:
            func_8BFA_b3(); break;
        case 0x80C2:
            switch (g_current_bank) {
                case 3: func_80C2_b3(); break;
                case 4: func_80C2_b4(); break;
                case 10: func_80C2_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x81A0:
            func_81A0_b3(); break;
        case 0x8500:
            switch (g_current_bank) {
                case 3: func_8500_b3(); break;
                case 8: func_8500_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xADEB:
            func_ADEB_b3(); break;
        case 0xBCD0:
            func_BCD0_b3(); break;
        case 0xA102:
            func_A102_b3(); break;
        case 0x8802:
            func_8802_b3(); break;
        case 0xAE04:
            switch (g_current_bank) {
                case 15: func_EE04(); break;
                case 3: func_AE04_b3(); break;
                case 14: func_AE04_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9E24:
            func_9E24_b3(); break;
        case 0x9C20:
            func_9C20_b3(); break;
        case 0x8DBE:
            func_8DBE_b3(); break;
        case 0x86CD:
            func_86CD_b3(); break;
        case 0x85AE:
            switch (g_current_bank) {
                case 3: func_85AE_b3(); break;
                case 5: func_85AE_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8DDD:
            func_8DDD_b3(); break;
        case 0x8E8E:
            func_8E8E_b3(); break;
        case 0xA18C:
            func_A18C_b3(); break;
        case 0xBFE8:
            func_BFE8_b3(); break;
        case 0xBFC2:
            switch (g_current_bank) {
                case 3: func_BFC2_b3(); break;
                case 5: func_BFC2_b5(); break;
                case 6: func_BFC2_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB9C0:
            func_B9C0_b3(); break;
        case 0x84BA:
            func_84BA_b3(); break;
        case 0x86A6:
            func_86A6_b3(); break;
        case 0x86A2:
            func_86A2_b3(); break;
        case 0x85BA:
            func_85BA_b3(); break;
        case 0xB08C:
            func_B08C_b3(); break;
        case 0x9F9E:
            func_9F9E_b3(); break;
        case 0x8DDF:
            func_8DDF_b3(); break;
        case 0xB397:
            func_B397_b3(); break;
        case 0xBBCF:
            func_BBCF_b3(); break;
        case 0x84EC:
            switch (g_current_bank) {
                case 3: func_84EC_b3(); break;
                case 2: func_84EC_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBBBC:
            switch (g_current_bank) {
                case 3: func_BBBC_b3(); break;
                case 4: func_BBBC_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x80A8:
            func_80A8_b3(); break;
        case 0x84B6:
            func_84B6_b3(); break;
        case 0x86C2:
            func_86C2_b3(); break;
        case 0x8FBD:
            switch (g_current_bank) {
                case 15: func_CFBD(); break;
                case 3: func_8FBD_b3(); break;
                case 14: func_8FBD_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8105:
            func_8105_b3(); break;
        case 0x8F19:
            func_8F19_b3(); break;
        case 0x9BFF:
            func_9BFF_b3(); break;
        case 0xA0B1:
            switch (g_current_bank) {
                case 3: func_A0B1_b3(); break;
                case 5: func_A0B1_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB2BC:
            switch (g_current_bank) {
                case 3: func_B2BC_b3(); break;
                case 8: func_B2BC_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAAAC:
            switch (g_current_bank) {
                case 15: func_EAAC(); break;
                case 3: func_AAAC_b3(); break;
                case 10: func_AAAC_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB3D0:
            func_B3D0_b3(); break;
        case 0xB3AC:
            func_B3AC_b3(); break;
        case 0xB3B4:
            func_B3B4_b3(); break;
        case 0xAABD:
            func_AABD_b3(); break;
        case 0xA7A4:
            switch (g_current_bank) {
                case 3: func_A7A4_b3(); break;
                case 14: func_A7A4_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA9AE:
            func_A9AE_b3(); break;
        case 0xBFAA:
            switch (g_current_bank) {
                case 3: func_BFAA_b3(); break;
                case 5: func_BFAA_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB9AC:
            func_B9AC_b3(); break;
        case 0xA9CE:
            func_A9CE_b3(); break;
        case 0xBECF:
            func_BECF_b3(); break;
        case 0xABAE:
            func_ABAE_b3(); break;
        case 0xB8BF:
            func_B8BF_b3(); break;
        case 0xB3AA:
            func_B3AA_b3(); break;
        case 0xAFCC:
            func_AFCC_b3(); break;
        case 0xA9E4:
            func_A9E4_b3(); break;
        case 0xB1A2:
            func_B1A2_b3(); break;
        case 0xB5B2:
            func_B5B2_b3(); break;
        case 0xB7B2:
            func_B7B2_b3(); break;
        case 0xB3F7:
            func_B3F7_b3(); break;
        case 0xA9A6:
            func_A9A6_b3(); break;
        case 0xBAAA:
            func_BAAA_b3(); break;
        case 0xB6AA:
            func_B6AA_b3(); break;
        case 0xB0D0:
            func_B0D0_b3(); break;
        case 0xBCFF:
            func_BCFF_b3(); break;
        case 0xBED2:
            func_BED2_b3(); break;
        case 0xB1B6:
            func_B1B6_b3(); break;
        case 0xB800:
            switch (g_current_bank) {
                case 15: func_F800(); break;
                case 3: func_B800_b3(); break;
                case 7: func_B800_b7(); break;
                case 4: func_B800_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9C8F:
            func_9C8F_b3(); break;
        case 0xB0DF:
            func_B0DF_b3(); break;
        case 0x84C6:
            func_84C6_b3(); break;
        case 0xAE84:
            func_AE84_b3(); break;
        case 0xBCCA:
            func_BCCA_b3(); break;
        case 0xB4EA:
            func_B4EA_b3(); break;
        case 0x8CBF:
            func_8CBF_b3(); break;
        case 0xB1E0:
            func_B1E0_b3(); break;
        case 0x9CBA:
            func_9CBA_b3(); break;
        case 0x8B8E:
            func_8B8E_b3(); break;
        case 0x9386:
            func_9386_b3(); break;
        case 0xA0A5:
            func_A0A5_b3(); break;
        case 0x9C8A:
            func_9C8A_b3(); break;
        case 0x9C86:
            func_9C86_b3(); break;
        case 0x9DB3:
            switch (g_current_bank) {
                case 3: func_9DB3_b3(); break;
                case 1: func_9DB3_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB784:
            func_B784_b3(); break;
        case 0xBFB8:
            func_BFB8_b3(); break;
        case 0x86C0:
            func_86C0_b3(); break;
        case 0x85E7:
            func_85E7_b3(); break;
        case 0x8781:
            switch (g_current_bank) {
                case 3: func_8781_b3(); break;
                case 6: func_8781_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBEB7:
            func_BEB7_b3(); break;
        case 0x8997:
            func_8997_b3(); break;
        case 0xB387:
            func_B387_b3(); break;
        case 0x9D01:
            switch (g_current_bank) {
                case 3: func_9D01_b3(); break;
                case 4: func_9D01_b4(); break;
                case 14: func_9D01_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9903:
            func_9903_b3(); break;
        case 0x9406:
            func_9406_b3(); break;
        case 0x9909:
            switch (g_current_bank) {
                case 3: func_9909_b3(); break;
                case 14: func_9909_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x990B:
            switch (g_current_bank) {
                case 3: func_990B_b3(); break;
                case 14: func_990B_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9D0D:
            func_9D0D_b3(); break;
        case 0x89BC:
            func_89BC_b3(); break;
        case 0x99E5:
            func_99E5_b3(); break;
        case 0xA0A1:
            func_A0A1_b3(); break;
        case 0x99E7:
            func_99E7_b3(); break;
        case 0x8DEA:
            func_8DEA_b3(); break;
        case 0x9D8E:
            func_9D8E_b3(); break;
        case 0x8A82:
            func_8A82_b3(); break;
        case 0xADAC:
            func_ADAC_b3(); break;
        case 0x90E7:
            func_90E7_b3(); break;
        case 0x90D5:
            func_90D5_b3(); break;
        case 0xA1FE:
            func_A1FE_b3(); break;
        case 0x8FA3:
            func_8FA3_b3(); break;
        case 0x92F2:
            func_92F2_b3(); break;
        case 0x9F9C:
            func_9F9C_b3(); break;
        case 0xA4F4:
            func_A4F4_b3(); break;
        case 0xA5E4:
            func_A5E4_b3(); break;
        case 0x9CEA:
            func_9CEA_b3(); break;
        case 0x9E15:
            func_9E15_b3(); break;
        case 0x9116:
            func_9116_b3(); break;
        case 0x99FC:
            func_99FC_b3(); break;
        case 0x90C4:
            func_90C4_b3(); break;
        case 0x97EA:
            func_97EA_b3(); break;
        case 0x9FD0:
            func_9FD0_b3(); break;
        case 0xA3E6:
            func_A3E6_b3(); break;
        case 0xA6A4:
            func_A6A4_b3(); break;
        case 0x98EB:
            switch (g_current_bank) {
                case 15: func_D8EB(); break;
                case 3: func_98EB_b3(); break;
                case 2: func_98EB_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8F9B:
            switch (g_current_bank) {
                case 3: func_8F9B_b3(); break;
                case 6: func_8F9B_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9001:
            switch (g_current_bank) {
                case 3: func_9001_b3(); break;
                case 5: func_9001_b5(); break;
                case 6: func_9001_b6(); break;
                case 8: func_9001_b8(); break;
                case 12: func_9001_b12(); break;
                case 14: func_9001_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x80D6:
            switch (g_current_bank) {
                case 3: func_80D6_b3(); break;
                case 2: func_80D6_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x80D2:
            func_80D2_b3(); break;
        case 0xBC00:
            switch (g_current_bank) {
                case 3: func_BC00_b3(); break;
                case 7: func_BC00_b7(); break;
                case 8: func_BC00_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9400:
            func_9400_b3(); break;
        case 0xBCFC:
            func_BCFC_b3(); break;
        case 0x8400:
            func_8400_b3(); break;
        case 0xB300:
            switch (g_current_bank) {
                case 3: func_B300_b3(); break;
                case 7: func_B300_b7(); break;
                case 8: func_B300_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBBDF:
            func_BBDF_b3(); break;
        case 0xBDF0:
            func_BDF0_b3(); break;
        case 0xB400:
            switch (g_current_bank) {
                case 3: func_B400_b3(); break;
                case 8: func_B400_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBA80:
            func_BA80_b3(); break;
        case 0x89C0:
            func_89C0_b3(); break;
        case 0xA000:
            switch (g_current_bank) {
                case 15: func_E000(); break;
                case 3: func_A000_b3(); break;
                case 8: func_A000_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x81F8:
            func_81F8_b3(); break;
        case 0x87F4:
            func_87F4_b3(); break;
        case 0x9A00:
            func_9A00_b3(); break;
        case 0xBFF8:
            switch (g_current_bank) {
                case 15: func_FFF8(); break;
                case 3: func_BFF8_b3(); break;
                case 6: func_BFF8_b6(); break;
                case 7: func_BFF8_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB1FF:
            switch (g_current_bank) {
                case 3: func_B1FF_b3(); break;
                case 0: func_B1FF_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8B00:
            switch (g_current_bank) {
                case 3: func_8B00_b3(); break;
                case 0: func_8B00_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA9FE:
            func_A9FE_b3(); break;
        case 0xA001:
            switch (g_current_bank) {
                case 15: func_E001(); break;
                case 4: func_A001_b4(); break;
                case 6: func_A001_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x99D9:
            func_99D9_b4(); break;
        case 0xBDEC:
            func_BDEC_b4(); break;
        case 0xA178:
            func_A178_b4(); break;
        case 0xB2A2:
            func_B2A2_b4(); break;
        case 0x8D9F:
            func_8D9F_b4(); break;
        case 0x8102:
            switch (g_current_bank) {
                case 4: func_8102_b4(); break;
                case 6: func_8102_b6(); break;
                case 10: func_8102_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA9B7:
            func_A9B7_b4(); break;
        case 0xA6EE:
            func_A6EE_b4(); break;
        case 0xBB78:
            func_BB78_b4(); break;
        case 0x99BC:
            func_99BC_b4(); break;
        case 0x9D0F:
            func_9D0F_b4(); break;
        case 0xAAD1:
            func_AAD1_b4(); break;
        case 0xAE01:
            func_AE01_b4(); break;
        case 0x8880:
            func_8880_b4(); break;
        case 0xB66E:
            func_B66E_b4(); break;
        case 0xA9ED:
            func_A9ED_b4(); break;
        case 0xAD43:
            func_AD43_b4(); break;
        case 0x8F20:
            func_8F20_b4(); break;
        case 0xB6DE:
            func_B6DE_b4(); break;
        case 0xA96A:
            func_A96A_b4(); break;
        case 0x8104:
            func_8104_b4(); break;
        case 0x8890:
            func_8890_b4(); break;
        case 0x999A:
            func_999A_b4(); break;
        case 0xA64D:
            func_A64D_b4(); break;
        case 0x88FA:
            func_88FA_b4(); break;
        case 0x9B08:
            func_9B08_b4(); break;
        case 0xB10B:
            func_B10B_b4(); break;
        case 0xAA81:
            func_AA81_b4(); break;
        case 0xB4B8:
            func_B4B8_b4(); break;
        case 0x96DB:
            func_96DB_b4(); break;
        case 0xA9D7:
            func_A9D7_b4(); break;
        case 0xB44B:
            func_B44B_b4(); break;
        case 0xBC84:
            func_BC84_b4(); break;
        case 0x8780:
            func_8780_b4(); break;
        case 0xB05F:
            func_B05F_b4(); break;
        case 0xA741:
            func_A741_b4(); break;
        case 0x9237:
            func_9237_b4(); break;
        case 0x8A0B:
            switch (g_current_bank) {
                case 4: func_8A0B_b4(); break;
                case 6: func_8A0B_b6(); break;
                case 12: func_8A0B_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x80EB:
            switch (g_current_bank) {
                case 4: func_80EB_b4(); break;
                case 2: func_80EB_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8D9D:
            func_8D9D_b4(); break;
        case 0xA041:
            func_A041_b4(); break;
        case 0xAB3D:
            func_AB3D_b4(); break;
        case 0xBD7B:
            func_BD7B_b4(); break;
        case 0xA3C9:
            func_A3C9_b4(); break;
        case 0xA8E3:
            func_A8E3_b4(); break;
        case 0xAD53:
            func_AD53_b4(); break;
        case 0x8100:
            func_8100_b4(); break;
        case 0xA938:
            func_A938_b4(); break;
        case 0x857B:
            func_857B_b4(); break;
        case 0x933A:
            func_933A_b4(); break;
        case 0xA876:
            func_A876_b4(); break;
        case 0x8BC4:
            func_8BC4_b4(); break;
        case 0xA3FF:
            func_A3FF_b4(); break;
        case 0xBE01:
            func_BE01_b4(); break;
        case 0x8ECD:
            func_8ECD_b4(); break;
        case 0x8E07:
            func_8E07_b4(); break;
        case 0x9255:
            func_9255_b4(); break;
        case 0xA011:
            func_A011_b4(); break;
        case 0xA374:
            func_A374_b4(); break;
        case 0x9FDE:
            func_9FDE_b4(); break;
        case 0xB8C0:
            func_B8C0_b4(); break;
        case 0x9AC3:
            func_9AC3_b4(); break;
        case 0xBDF3:
            func_BDF3_b4(); break;
        case 0xA0BE:
            func_A0BE_b4(); break;
        case 0xA6A1:
            func_A6A1_b4(); break;
        case 0x81C3:
            func_81C3_b4(); break;
        case 0x8282:
            func_8282_b4(); break;
        case 0x8181:
            switch (g_current_bank) {
                case 4: func_8181_b4(); break;
                case 6: func_8181_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9DDE:
            func_9DDE_b4(); break;
        case 0xA404:
            func_A404_b4(); break;
        case 0xA2A2:
            switch (g_current_bank) {
                case 4: func_A2A2_b4(); break;
                case 12: func_A2A2_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA4A5:
            func_A4A5_b4(); break;
        case 0x8188:
            func_8188_b4(); break;
        case 0x9C81:
            func_9C81_b4(); break;
        case 0x86A5:
            func_86A5_b4(); break;
        case 0x9136:
            func_9136_b4(); break;
        case 0xBAFB:
            func_BAFB_b4(); break;
        case 0x84CF:
            func_84CF_b4(); break;
        case 0xA57B:
            func_A57B_b4(); break;
        case 0xB2A6:
            func_B2A6_b4(); break;
        case 0xA9B3:
            func_A9B3_b4(); break;
        case 0xB6E3:
            func_B6E3_b4(); break;
        case 0x8E8F:
            func_8E8F_b4(); break;
        case 0x9287:
            switch (g_current_bank) {
                case 4: func_9287_b4(); break;
                case 14: func_9287_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x908A:
            func_908A_b4(); break;
        case 0x8B8C:
            func_8B8C_b4(); break;
        case 0x908C:
            func_908C_b4(); break;
        case 0xB682:
            func_B682_b4(); break;
        case 0x8601:
            switch (g_current_bank) {
                case 4: func_8601_b4(); break;
                case 8: func_8601_b8(); break;
                case 13: func_8601_b13(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA401:
            func_A401_b4(); break;
        case 0x98D1:
            func_98D1_b4(); break;
        case 0x8721:
            switch (g_current_bank) {
                case 4: func_8721_b4(); break;
                case 14: func_8721_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB0C3:
            switch (g_current_bank) {
                case 4: func_B0C3_b4(); break;
                case 2: func_B0C3_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA095:
            func_A095_b4(); break;
        case 0xA007:
            func_A007_b4(); break;
        case 0xB043:
            func_B043_b4(); break;
        case 0xBE40:
            func_BE40_b4(); break;
        case 0xB878:
            func_B878_b4(); break;
        case 0xB363:
            func_B363_b4(); break;
        case 0x8075:
            func_8075_b4(); break;
        case 0x9573:
            func_9573_b4(); break;
        case 0xB8F5:
            func_B8F5_b4(); break;
        case 0xBA6B:
            func_BA6B_b4(); break;
        case 0x8B9E:
            func_8B9E_b4(); break;
        case 0x8F8C:
            func_8F8C_b4(); break;
        case 0xAF33:
            func_AF33_b4(); break;
        case 0x806C:
            func_806C_b4(); break;
        case 0x9E88:
            func_9E88_b4(); break;
        case 0xA3F6:
            func_A3F6_b4(); break;
        case 0xB6B2:
            func_B6B2_b4(); break;
        case 0xBF39:
            func_BF39_b4(); break;
        case 0xAAFA:
            switch (g_current_bank) {
                case 4: func_AAFA_b4(); break;
                case 14: func_AAFA_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8808:
            switch (g_current_bank) {
                case 15: func_C808(); break;
                case 4: func_8808_b4(); break;
                case 11: func_8808_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8071:
            switch (g_current_bank) {
                case 4: func_8071_b4(); break;
                case 6: func_8071_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8F42:
            func_8F42_b4(); break;
        case 0x95B7:
            func_95B7_b4(); break;
        case 0x9A01:
            func_9A01_b4(); break;
        case 0x87D3:
            func_87D3_b4(); break;
        case 0xAC60:
            func_AC60_b4(); break;
        case 0xB1FA:
            func_B1FA_b4(); break;
        case 0xA501:
            switch (g_current_bank) {
                case 4: func_A501_b4(); break;
                case 14: func_A501_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA521:
            func_A521_b4(); break;
        case 0x8063:
            switch (g_current_bank) {
                case 4: func_8063_b4(); break;
                case 6: func_8063_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x930A:
            func_930A_b4(); break;
        case 0x86CC:
            func_86CC_b4(); break;
        case 0x8A85:
            func_8A85_b4(); break;
        case 0xA716:
            func_A716_b4(); break;
        case 0x8021:
            switch (g_current_bank) {
                case 4: func_8021_b4(); break;
                case 8: func_8021_b8(); break;
                case 12: func_8021_b12(); break;
                case 14: func_8021_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAF41:
            func_AF41_b4(); break;
        case 0x88B0:
            func_88B0_b4(); break;
        case 0x83C1:
            switch (g_current_bank) {
                case 4: func_83C1_b4(); break;
                case 7: func_83C1_b7(); break;
                case 14: func_83C1_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9D81:
            switch (g_current_bank) {
                case 4: func_9D81_b4(); break;
                case 14: func_9D81_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAB08:
            func_AB08_b4(); break;
        case 0xB4C1:
            func_B4C1_b4(); break;
        case 0xA724:
            func_A724_b4(); break;
        case 0xA358:
            func_A358_b4(); break;
        case 0xB6E8:
            func_B6E8_b4(); break;
        case 0x87E0:
            func_87E0_b4(); break;
        case 0x9BEF:
            switch (g_current_bank) {
                case 15: func_DBEF(); break;
                case 4: func_9BEF_b4(); break;
                case 6: func_9BEF_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x88F4:
            func_88F4_b4(); break;
        case 0xACCE:
            func_ACCE_b4(); break;
        case 0xA915:
            func_A915_b4(); break;
        case 0x90B5:
            switch (g_current_bank) {
                case 4: func_90B5_b4(); break;
                case 6: func_90B5_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAF01:
            func_AF01_b4(); break;
        case 0xA43A:
            func_A43A_b4(); break;
        case 0xA0C1:
            func_A0C1_b4(); break;
        case 0xB01B:
            func_B01B_b4(); break;
        case 0x8217:
            func_8217_b4(); break;
        case 0x9115:
            func_9115_b4(); break;
        case 0xA25E:
            func_A25E_b4(); break;
        case 0xAC80:
            func_AC80_b4(); break;
        case 0x8C5B:
            switch (g_current_bank) {
                case 4: func_8C5B_b4(); break;
                case 2: func_8C5B_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x91A1:
            func_91A1_b4(); break;
        case 0x9497:
            switch (g_current_bank) {
                case 4: func_9497_b4(); break;
                case 14: func_9497_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA258:
            func_A258_b4(); break;
        case 0x8525:
            switch (g_current_bank) {
                case 4: func_8525_b4(); break;
                case 12: func_8525_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8862:
            func_8862_b4(); break;
        case 0xB338:
            func_B338_b4(); break;
        case 0x93E0:
            func_93E0_b4(); break;
        case 0x8EC7:
            func_8EC7_b4(); break;
        case 0xAEC2:
            func_AEC2_b4(); break;
        case 0x80AD:
            func_80AD_b4(); break;
        case 0x9A8F:
            func_9A8F_b4(); break;
        case 0xACD7:
            func_ACD7_b4(); break;
        case 0xA5C0:
            func_A5C0_b4(); break;
        case 0xBFA6:
            func_BFA6_b4(); break;
        case 0x8109:
            func_8109_b4(); break;
        case 0xA0A2:
            func_A0A2_b4(); break;
        case 0x9600:
            func_9600_b4(); break;
        case 0xB071:
            func_B071_b4(); break;
        case 0xBCDE:
            switch (g_current_bank) {
                case 4: func_BCDE_b4(); break;
                case 14: func_BCDE_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9EAF:
            func_9EAF_b4(); break;
        case 0xAEB1:
            func_AEB1_b4(); break;
        case 0xAE9F:
            func_AE9F_b4(); break;
        case 0xB6FA:
            func_B6FA_b4(); break;
        case 0x8934:
            func_8934_b4(); break;
        case 0xA6E3:
            func_A6E3_b4(); break;
        case 0xA6A7:
            func_A6A7_b4(); break;
        case 0xAFD0:
            func_AFD0_b4(); break;
        case 0x8CCD:
            switch (g_current_bank) {
                case 4: func_8CCD_b4(); break;
                case 6: func_8CCD_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB488:
            func_B488_b4(); break;
        case 0xB501:
            func_B501_b4(); break;
        case 0x8876:
            func_8876_b4(); break;
        case 0x9D41:
            switch (g_current_bank) {
                case 15: func_DD41(); break;
                case 4: func_9D41_b4(); break;
                case 14: func_9D41_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8B4C:
            func_8B4C_b4(); break;
        case 0x9143:
            func_9143_b4(); break;
        case 0x8B90:
            func_8B90_b4(); break;
        case 0x8885:
            func_8885_b4(); break;
        case 0x8C7C:
            func_8C7C_b4(); break;
        case 0x8A03:
            func_8A03_b4(); break;
        case 0x9495:
            func_9495_b4(); break;
        case 0x9B81:
            func_9B81_b4(); break;
        case 0x9BBC:
            func_9BBC_b4(); break;
        case 0x8341:
            func_8341_b4(); break;
        case 0x9F96:
            func_9F96_b4(); break;
        case 0x9F01:
            switch (g_current_bank) {
                case 4: func_9F01_b4(); break;
                case 6: func_9F01_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8423:
            func_8423_b4(); break;
        case 0x9432:
            func_9432_b4(); break;
        case 0xA8AA:
            func_A8AA_b4(); break;
        case 0x8A48:
            func_8A48_b4(); break;
        case 0xB0D9:
            switch (g_current_bank) {
                case 4: func_B0D9_b4(); break;
                case 6: func_B0D9_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA372:
            func_A372_b4(); break;
        case 0xB022:
            func_B022_b4(); break;
        case 0xA2A8:
            func_A2A8_b4(); break;
        case 0x8097:
            func_8097_b4(); break;
        case 0xA4B1:
            func_A4B1_b4(); break;
        case 0x8697:
            func_8697_b4(); break;
        case 0x9487:
            func_9487_b4(); break;
        case 0xAB01:
            func_AB01_b4(); break;
        case 0x9253:
            func_9253_b4(); break;
        case 0x8023:
            func_8023_b4(); break;
        case 0x89A3:
            func_89A3_b4(); break;
        case 0xA9FB:
            func_A9FB_b4(); break;
        case 0x9102:
            func_9102_b4(); break;
        case 0x9B95:
            func_9B95_b4(); break;
        case 0xBAFD:
            func_BAFD_b4(); break;
        case 0x817D:
            func_817D_b4(); break;
        case 0x94A3:
            func_94A3_b4(); break;
        case 0x8EAE:
            func_8EAE_b4(); break;
        case 0xBE07:
            func_BE07_b4(); break;
        case 0x9413:
            func_9413_b4(); break;
        case 0xB5B3:
            func_B5B3_b4(); break;
        case 0x8509:
            func_8509_b4(); break;
        case 0x8E8D:
            func_8E8D_b4(); break;
        case 0x9CED:
            switch (g_current_bank) {
                case 4: func_9CED_b4(); break;
                case 14: func_9CED_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAE27:
            func_AE27_b4(); break;
        case 0xAB95:
            func_AB95_b4(); break;
        case 0xB4EF:
            func_B4EF_b4(); break;
        case 0xA272:
            func_A272_b4(); break;
        case 0x9361:
            func_9361_b4(); break;
        case 0xAD01:
            func_AD01_b4(); break;
        case 0x8487:
            func_8487_b4(); break;
        case 0x9C34:
            func_9C34_b4(); break;
        case 0xA906:
            func_A906_b4(); break;
        case 0x840B:
            func_840B_b4(); break;
        case 0xAA98:
            func_AA98_b4(); break;
        case 0xAA12:
            func_AA12_b4(); break;
        case 0xAA58:
            func_AA58_b4(); break;
        case 0xAD11:
            func_AD11_b4(); break;
        case 0xA158:
            func_A158_b4(); break;
        case 0x82F8:
            switch (g_current_bank) {
                case 4: func_82F8_b4(); break;
                case 14: func_82F8_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA982:
            func_A982_b5(); break;
        case 0x8DFC:
            func_8DFC_b5(); break;
        case 0xA941:
            switch (g_current_bank) {
                case 5: func_A941_b5(); break;
                case 14: func_A941_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB908:
            func_B908_b5(); break;
        case 0x958F:
            func_958F_b5(); break;
        case 0x8EE9:
            func_8EE9_b5(); break;
        case 0x90AA:
            switch (g_current_bank) {
                case 15: func_D0AA(); break;
                case 5: func_90AA_b5(); break;
                case 14: func_90AA_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8D91:
            func_8D91_b5(); break;
        case 0xBD02:
            switch (g_current_bank) {
                case 5: func_BD02_b5(); break;
                case 1: func_BD02_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBC02:
            func_BC02_b5(); break;
        case 0x8828:
            func_8828_b5(); break;
        case 0x8D10:
            func_8D10_b5(); break;
        case 0x900E:
            func_900E_b5(); break;
        case 0x81DD:
            func_81DD_b5(); break;
        case 0x9013:
            func_9013_b5(); break;
        case 0xA802:
            func_A802_b5(); break;
        case 0x90EF:
            switch (g_current_bank) {
                case 5: func_90EF_b5(); break;
                case 4: func_90EF_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x826B:
            func_826B_b5(); break;
        case 0x8458:
            func_8458_b5(); break;
        case 0x843D:
            func_843D_b5(); break;
        case 0x8480:
            func_8480_b5(); break;
        case 0x848F:
            func_848F_b5(); break;
        case 0x84D0:
            func_84D0_b5(); break;
        case 0x8502:
            func_8502_b5(); break;
        case 0x84F0:
            func_84F0_b5(); break;
        case 0x84B7:
            func_84B7_b5(); break;
        case 0x9485:
            func_9485_b5(); break;
        case 0x8295:
            func_8295_b5(); break;
        case 0x8483:
            func_8483_b5(); break;
        case 0x8517:
            func_8517_b5(); break;
        case 0x8523:
            func_8523_b5(); break;
        case 0x852F:
            func_852F_b5(); break;
        case 0x853B:
            func_853B_b5(); break;
        case 0x8D4B:
            switch (g_current_bank) {
                case 5: func_8D4B_b5(); break;
                case 12: func_8D4B_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA916:
            func_A916_b5(); break;
        case 0x8570:
            func_8570_b5(); break;
        case 0x8580:
            switch (g_current_bank) {
                case 5: func_8580_b5(); break;
                case 12: func_8580_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA93E:
            func_A93E_b5(); break;
        case 0x8DF9:
            func_8DF9_b5(); break;
        case 0xA984:
            func_A984_b5(); break;
        case 0xAC41:
            func_AC41_b5(); break;
        case 0x88FC:
            switch (g_current_bank) {
                case 15: func_C8FC(); break;
                case 5: func_88FC_b5(); break;
                case 4: func_88FC_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB502:
            func_B502_b5(); break;
        case 0x8A0E:
            func_8A0E_b5(); break;
        case 0x9502:
            func_9502_b5(); break;
        case 0xB906:
            func_B906_b5(); break;
        case 0xBF04:
            func_BF04_b5(); break;
        case 0x8005:
            switch (g_current_bank) {
                case 5: func_8005_b5(); break;
                case 6: func_8005_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8ECE:
            func_8ECE_b5(); break;
        case 0x8E76:
            func_8E76_b5(); break;
        case 0x8D2C:
            switch (g_current_bank) {
                case 5: func_8D2C_b5(); break;
                case 7: func_8D2C_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8DB9:
            func_8DB9_b5(); break;
        case 0x8621:
            func_8621_b5(); break;
        case 0x8A7E:
            switch (g_current_bank) {
                case 5: func_8A7E_b5(); break;
                case 1: func_8A7E_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8A3D:
            func_8A3D_b5(); break;
        case 0x886D:
            func_886D_b5(); break;
        case 0x88C5:
            func_88C5_b5(); break;
        case 0x8AD0:
            func_8AD0_b5(); break;
        case 0x8734:
            switch (g_current_bank) {
                case 5: func_8734_b5(); break;
                case 6: func_8734_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x87B5:
            func_87B5_b5(); break;
        case 0x90BE:
            func_90BE_b5(); break;
        case 0xB075:
            func_B075_b5(); break;
        case 0xAA03:
            func_AA03_b5(); break;
        case 0x8725:
            switch (g_current_bank) {
                case 5: func_8725_b5(); break;
                case 11: func_8725_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8D33:
            func_8D33_b5(); break;
        case 0x8D3D:
            func_8D3D_b5(); break;
        case 0x8D38:
            func_8D38_b5(); break;
        case 0xA808:
            switch (g_current_bank) {
                case 15: func_E808(); break;
                case 5: func_A808_b5(); break;
                case 14: func_A808_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA904:
            func_A904_b5(); break;
        case 0xAE36:
            func_AE36_b5(); break;
        case 0x88B5:
            func_88B5_b5(); break;
        case 0x900A:
            switch (g_current_bank) {
                case 15: func_D00A(); break;
                case 5: func_900A_b5(); break;
                case 12: func_900A_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x93B9:
            func_93B9_b5(); break;
        case 0x8A7A:
            func_8A7A_b5(); break;
        case 0x8EAA:
            func_8EAA_b5(); break;
        case 0x86AA:
            func_86AA_b5(); break;
        case 0xA90E:
            switch (g_current_bank) {
                case 15: func_E90E(); break;
                case 5: func_A90E_b5(); break;
                case 14: func_A90E_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8DA4:
            func_8DA4_b5(); break;
        case 0x8D13:
            func_8D13_b5(); break;
        case 0xABFE:
            func_ABFE_b5(); break;
        case 0x8D19:
            switch (g_current_bank) {
                case 5: func_8D19_b5(); break;
                case 12: func_8D19_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8D04:
            switch (g_current_bank) {
                case 15: func_CD04(); break;
                case 5: func_8D04_b5(); break;
                case 1: func_8D04_b1(); break;
                case 14: func_8D04_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB5BE:
            func_B5BE_b5(); break;
        case 0x8E60:
            func_8E60_b5(); break;
        case 0x8EC6:
            func_8EC6_b5(); break;
        case 0xBD9C:
            func_BD9C_b5(); break;
        case 0xB1A0:
            func_B1A0_b5(); break;
        case 0xBBA6:
            func_BBA6_b5(); break;
        case 0xB9A8:
            func_B9A8_b5(); break;
        case 0xB003:
            func_B003_b5(); break;
        case 0x983C:
            func_983C_b5(); break;
        case 0x8C3D:
            func_8C3D_b5(); break;
        case 0xBC3A:
            func_BC3A_b5(); break;
        case 0x8602:
            func_8602_b5(); break;
        case 0x8638:
            func_8638_b5(); break;
        case 0x9803:
            switch (g_current_bank) {
                case 5: func_9803_b5(); break;
                case 6: func_9803_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8631:
            func_8631_b5(); break;
        case 0x9836:
            func_9836_b5(); break;
        case 0x983A:
            func_983A_b5(); break;
        case 0x8C35:
            func_8C35_b5(); break;
        case 0x8C11:
            func_8C11_b5(); break;
        case 0x8C18:
            func_8C18_b5(); break;
        case 0x983E:
            func_983E_b5(); break;
        case 0xB03A:
            func_B03A_b5(); break;
        case 0x9842:
            func_9842_b5(); break;
        case 0x8C2E:
            func_8C2E_b5(); break;
        case 0x8636:
            func_8636_b5(); break;
        case 0x8633:
            func_8633_b5(); break;
        case 0x8617:
            func_8617_b5(); break;
        case 0xBC36:
            func_BC36_b5(); break;
        case 0xB037:
            func_B037_b5(); break;
        case 0x8C2B:
            func_8C2B_b5(); break;
        case 0x8606:
            switch (g_current_bank) {
                case 15: func_C606(); break;
                case 5: func_8606_b5(); break;
                case 12: func_8606_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C20:
            func_8C20_b5(); break;
        case 0xA40E:
            switch (g_current_bank) {
                case 5: func_A40E_b5(); break;
                case 8: func_A40E_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x882B:
            func_882B_b5(); break;
        case 0x903A:
            func_903A_b5(); break;
        case 0x881B:
            func_881B_b5(); break;
        case 0x8838:
            func_8838_b5(); break;
        case 0x8831:
            func_8831_b5(); break;
        case 0xA036:
            func_A036_b5(); break;
        case 0xA03B:
            func_A03B_b5(); break;
        case 0x9C36:
            func_9C36_b5(); break;
        case 0x9019:
            switch (g_current_bank) {
                case 5: func_9019_b5(); break;
                case 6: func_9019_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8814:
            func_8814_b5(); break;
        case 0x9020:
            switch (g_current_bank) {
                case 15: func_D020(); break;
                case 5: func_9020_b5(); break;
                case 4: func_9020_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x982E:
            func_982E_b5(); break;
        case 0xA038:
            func_A038_b5(); break;
        case 0x903D:
            func_903D_b5(); break;
        case 0x9041:
            func_9041_b5(); break;
        case 0x953C:
            func_953C_b5(); break;
        case 0x9034:
            func_9034_b5(); break;
        case 0x8A04:
            switch (g_current_bank) {
                case 15: func_CA04(); break;
                case 5: func_8A04_b5(); break;
                case 14: func_8A04_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8F03:
            func_8F03_b5(); break;
        case 0x873B:
            func_873B_b5(); break;
        case 0x8712:
            func_8712_b5(); break;
        case 0x8640:
            func_8640_b5(); break;
        case 0x883F:
            func_883F_b5(); break;
        case 0xAC03:
            switch (g_current_bank) {
                case 5: func_AC03_b5(); break;
                case 14: func_AC03_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8B38:
            func_8B38_b5(); break;
        case 0x8B3F:
            func_8B3F_b5(); break;
        case 0x963F:
            func_963F_b5(); break;
        case 0xAC30:
            func_AC30_b5(); break;
        case 0x962E:
            func_962E_b5(); break;
        case 0x8E30:
            func_8E30_b5(); break;
        case 0x8727:
            func_8727_b5(); break;
        case 0x97EF:
            func_97EF_b5(); break;
        case 0x9702:
            func_9702_b5(); break;
        case 0xAB00:
            func_AB00_b5(); break;
        case 0xB630:
            func_B630_b5(); break;
        case 0x9F33:
            func_9F33_b5(); break;
        case 0xBFCC:
            func_BFCC_b5(); break;
        case 0x9F6A:
            func_9F6A_b5(); break;
        case 0xBF36:
            func_BF36_b5(); break;
        case 0xB000:
            func_B000_b5(); break;
        case 0x8EA0:
            func_8EA0_b5(); break;
        case 0xB7A4:
            switch (g_current_bank) {
                case 5: func_B7A4_b5(); break;
                case 6: func_B7A4_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8A00:
            func_8A00_b5(); break;
        case 0xBD00:
            switch (g_current_bank) {
                case 5: func_BD00_b5(); break;
                case 8: func_BD00_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAFDD:
            func_AFDD_b5(); break;
        case 0x8B3A:
            func_8B3A_b5(); break;
        case 0xAFB6:
            switch (g_current_bank) {
                case 5: func_AFB6_b5(); break;
                case 14: func_AFB6_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB900:
            switch (g_current_bank) {
                case 5: func_B900_b5(); break;
                case 8: func_B900_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8F2C:
            func_8F2C_b5(); break;
        case 0xBFCE:
            func_BFCE_b5(); break;
        case 0xBDDF:
            func_BDDF_b5(); break;
        case 0x9C00:
            switch (g_current_bank) {
                case 5: func_9C00_b5(); break;
                case 7: func_9C00_b7(); break;
                case 8: func_9C00_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBF4A:
            func_BF4A_b5(); break;
        case 0xA6E6:
            func_A6E6_b5(); break;
        case 0xB87C:
            func_B87C_b5(); break;
        case 0xB946:
            func_B946_b5(); break;
        case 0xBDEA:
            func_BDEA_b5(); break;
        case 0x920E:
            func_920E_b6(); break;
        case 0x9211:
            func_9211_b6(); break;
        case 0xA236:
            switch (g_current_bank) {
                case 6: func_A236_b6(); break;
                case 14: func_A236_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA23D:
            func_A23D_b6(); break;
        case 0xB001:
            switch (g_current_bank) {
                case 6: func_B001_b6(); break;
                case 14: func_B001_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBE5F:
            func_BE5F_b6(); break;
        case 0xA051:
            func_A051_b6(); break;
        case 0xA0E1:
            func_A0E1_b6(); break;
        case 0x90E1:
            switch (g_current_bank) {
                case 15: func_D0E1(); break;
                case 6: func_90E1_b6(); break;
                case 7: func_90E1_b7(); break;
                case 14: func_90E1_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB693:
            func_B693_b6(); break;
        case 0x8839:
            func_8839_b6(); break;
        case 0xAFE1:
            func_AFE1_b6(); break;
        case 0xB8DD:
            func_B8DD_b6(); break;
        case 0x80FF:
            switch (g_current_bank) {
                case 15: func_C0FF(); break;
                case 6: func_80FF_b6(); break;
                case 8: func_80FF_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBE9F:
            func_BE9F_b6(); break;
        case 0xAF40:
            func_AF40_b6(); break;
        case 0xBEBF:
            switch (g_current_bank) {
                case 6: func_BEBF_b6(); break;
                case 7: func_BEBF_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x875F:
            func_875F_b6(); break;
        case 0xBE3F:
            switch (g_current_bank) {
                case 6: func_BE3F_b6(); break;
                case 7: func_BE3F_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBE37:
            func_BE37_b6(); break;
        case 0x8861:
            func_8861_b6(); break;
        case 0x86F7:
            func_86F7_b6(); break;
        case 0x9C5F:
            func_9C5F_b6(); break;
        case 0x8E19:
            func_8E19_b6(); break;
        case 0x84AD:
            func_84AD_b6(); break;
        case 0x80BA:
            func_80BA_b6(); break;
        case 0xBEDF:
            func_BEDF_b6(); break;
        case 0xACB1:
            func_ACB1_b6(); break;
        case 0xB0E1:
            func_B0E1_b6(); break;
        case 0x8C6D:
            func_8C6D_b6(); break;
        case 0xAE5D:
            func_AE5D_b6(); break;
        case 0xBF3F:
            func_BF3F_b6(); break;
        case 0x8E47:
            func_8E47_b6(); break;
        case 0x9FE4:
            func_9FE4_b6(); break;
        case 0x805D:
            func_805D_b6(); break;
        case 0xBF60:
            switch (g_current_bank) {
                case 6: func_BF60_b6(); break;
                case 7: func_BF60_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8D80:
            switch (g_current_bank) {
                case 6: func_8D80_b6(); break;
                case 14: func_8D80_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9841:
            func_9841_b6(); break;
        case 0xBC3D:
            func_BC3D_b6(); break;
        case 0xB160:
            func_B160_b6(); break;
        case 0x9C2D:
            func_9C2D_b6(); break;
        case 0x8CCB:
            func_8CCB_b6(); break;
        case 0x86BF:
            switch (g_current_bank) {
                case 15: func_C6BF(); break;
                case 6: func_86BF_b6(); break;
                case 11: func_86BF_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB687:
            func_B687_b6(); break;
        case 0x8302:
            switch (g_current_bank) {
                case 6: func_8302_b6(); break;
                case 12: func_8302_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB8C1:
            func_B8C1_b6(); break;
        case 0xA0F1:
            func_A0F1_b6(); break;
        case 0xAFB0:
            switch (g_current_bank) {
                case 6: func_AFB0_b6(); break;
                case 8: func_AFB0_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAE91:
            func_AE91_b6(); break;
        case 0xA800:
            func_A800_b6(); break;
        case 0xAC55:
            func_AC55_b6(); break;
        case 0xB650:
            func_B650_b6(); break;
        case 0xADE6:
            func_ADE6_b6(); break;
        case 0xBCC1:
            func_BCC1_b6(); break;
        case 0x8708:
            func_8708_b6(); break;
        case 0xA061:
            switch (g_current_bank) {
                case 6: func_A061_b6(); break;
                case 10: func_A061_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBAF5:
            func_BAF5_b6(); break;
        case 0x8041:
            func_8041_b6(); break;
        case 0x8C1B:
            func_8C1B_b6(); break;
        case 0x803F:
            func_803F_b6(); break;
        case 0xA99F:
            func_A99F_b6(); break;
        case 0x8E79:
            func_8E79_b6(); break;
        case 0xB8F1:
            func_B8F1_b6(); break;
        case 0x8674:
            func_8674_b6(); break;
        case 0xBF50:
            func_BF50_b6(); break;
        case 0x98CD:
            func_98CD_b6(); break;
        case 0x8031:
            func_8031_b6(); break;
        case 0xBF82:
            func_BF82_b6(); break;
        case 0x81E1:
            func_81E1_b6(); break;
        case 0x90B1:
            switch (g_current_bank) {
                case 6: func_90B1_b6(); break;
                case 2: func_90B1_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x90E9:
            func_90E9_b6(); break;
        case 0xA07F:
            func_A07F_b6(); break;
        case 0x86E7:
            func_86E7_b6(); break;
        case 0x907A:
            func_907A_b6(); break;
        case 0x90C9:
            func_90C9_b6(); break;
        case 0x9BBE:
            func_9BBE_b6(); break;
        case 0xB665:
            func_B665_b6(); break;
        case 0xB801:
            func_B801_b6(); break;
        case 0xBF48:
            func_BF48_b6(); break;
        case 0x84C2:
            func_84C2_b6(); break;
        case 0x8185:
            func_8185_b6(); break;
        case 0x884D:
            func_884D_b6(); break;
        case 0x8C1D:
            func_8C1D_b6(); break;
        case 0x853A:
            func_853A_b6(); break;
        case 0xA851:
            func_A851_b6(); break;
        case 0x9E4F:
            switch (g_current_bank) {
                case 6: func_9E4F_b6(); break;
                case 14: func_9E4F_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9E7D:
            func_9E7D_b6(); break;
        case 0x9C89:
            switch (g_current_bank) {
                case 6: func_9C89_b6(); break;
                case 14: func_9C89_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8069:
            func_8069_b6(); break;
        case 0xB4E5:
            func_B4E5_b6(); break;
        case 0xBEE7:
            func_BEE7_b6(); break;
        case 0x804D:
            func_804D_b6(); break;
        case 0xAFC8:
            func_AFC8_b6(); break;
        case 0x9464:
            func_9464_b6(); break;
        case 0x86F4:
            func_86F4_b6(); break;
        case 0xB7CC:
            func_B7CC_b6(); break;
        case 0x8082:
            switch (g_current_bank) {
                case 6: func_8082_b6(); break;
                case 8: func_8082_b8(); break;
                case 10: func_8082_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB3D9:
            func_B3D9_b6(); break;
        case 0x8382:
            func_8382_b6(); break;
        case 0xB079:
            func_B079_b6(); break;
        case 0x9CB9:
            func_9CB9_b6(); break;
        case 0xB899:
            switch (g_current_bank) {
                case 6: func_B899_b6(); break;
                case 14: func_B899_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C19:
            func_8C19_b6(); break;
        case 0xB039:
            func_B039_b6(); break;
        case 0x9A91:
            func_9A91_b6(); break;
        case 0x9332:
            func_9332_b6(); break;
        case 0xA457:
            func_A457_b6(); break;
        case 0xA76F:
            func_A76F_b6(); break;
        case 0xAC00:
            switch (g_current_bank) {
                case 6: func_AC00_b6(); break;
                case 7: func_AC00_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB9B1:
            func_B9B1_b6(); break;
        case 0x9A6C:
            func_9A6C_b6(); break;
        case 0x9CFB:
            func_9CFB_b6(); break;
        case 0x9654:
            func_9654_b6(); break;
        case 0xA71D:
            func_A71D_b6(); break;
        case 0xAAB4:
            func_AAB4_b6(); break;
        case 0x93E8:
            func_93E8_b6(); break;
        case 0xADFC:
            func_ADFC_b6(); break;
        case 0xACDA:
            func_ACDA_b6(); break;
        case 0x9943:
            func_9943_b6(); break;
        case 0x873A:
            func_873A_b6(); break;
        case 0xBF7F:
            func_BF7F_b6(); break;
        case 0x8ED8:
            func_8ED8_b6(); break;
        case 0xB8B9:
            func_B8B9_b6(); break;
        case 0xACCF:
            func_ACCF_b6(); break;
        case 0xB420:
            func_B420_b6(); break;
        case 0xBFE0:
            func_BFE0_b6(); break;
        case 0xBFBF:
            func_BFBF_b6(); break;
        case 0x9EC0:
            func_9EC0_b6(); break;
        case 0xB835:
            func_B835_b6(); break;
        case 0x851E:
            func_851E_b6(); break;
        case 0x813E:
            func_813E_b6(); break;
        case 0x817A:
            switch (g_current_bank) {
                case 6: func_817A_b6(); break;
                case 8: func_817A_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x88A3:
            switch (g_current_bank) {
                case 6: func_88A3_b6(); break;
                case 11: func_88A3_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBC5F:
            func_BC5F_b6(); break;
        case 0xBFC4:
            func_BFC4_b6(); break;
        case 0xA2F7:
            switch (g_current_bank) {
                case 6: func_A2F7_b6(); break;
                case 14: func_A2F7_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8D0A:
            switch (g_current_bank) {
                case 6: func_8D0A_b6(); break;
                case 14: func_8D0A_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBF10:
            func_BF10_b6(); break;
        case 0xADB9:
            func_ADB9_b6(); break;
        case 0xB2AE:
            func_B2AE_b6(); break;
        case 0x8C10:
            func_8C10_b6(); break;
        case 0x9B01:
            func_9B01_b6(); break;
        case 0xA2E5:
            func_A2E5_b6(); break;
        case 0x9805:
            func_9805_b6(); break;
        case 0x8B06:
            func_8B06_b6(); break;
        case 0x8778:
            func_8778_b6(); break;
        case 0xB563:
            func_B563_b6(); break;
        case 0xB371:
            func_B371_b6(); break;
        case 0x946F:
            func_946F_b6(); break;
        case 0x9F90:
            func_9F90_b6(); break;
        case 0x8FE8:
            func_8FE8_b6(); break;
        case 0x83FD:
            func_83FD_b6(); break;
        case 0xB3BC:
            func_B3BC_b6(); break;
        case 0x869D:
            switch (g_current_bank) {
                case 6: func_869D_b6(); break;
                case 8: func_869D_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBC48:
            func_BC48_b6(); break;
        case 0x8503:
            switch (g_current_bank) {
                case 15: func_C503(); break;
                case 6: func_8503_b6(); break;
                case 1: func_8503_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB77C:
            func_B77C_b6(); break;
        case 0xBB9C:
            switch (g_current_bank) {
                case 6: func_BB9C_b6(); break;
                case 14: func_BB9C_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB6BB:
            func_B6BB_b6(); break;
        case 0x8788:
            switch (g_current_bank) {
                case 6: func_8788_b6(); break;
                case 8: func_8788_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB8A9:
            func_B8A9_b6(); break;
        case 0x8CE3:
            func_8CE3_b6(); break;
        case 0x9F09:
            func_9F09_b6(); break;
        case 0xB679:
            func_B679_b6(); break;
        case 0xB754:
            func_B754_b6(); break;
        case 0xBB94:
            func_BB94_b6(); break;
        case 0x99CA:
            func_99CA_b6(); break;
        case 0x960C:
            func_960C_b6(); break;
        case 0xBCA7:
            func_BCA7_b6(); break;
        case 0xB839:
            func_B839_b6(); break;
        case 0x8809:
            func_8809_b6(); break;
        case 0xB8C9:
            func_B8C9_b6(); break;
        case 0xB09C:
            func_B09C_b6(); break;
        case 0xA1C3:
            func_A1C3_b6(); break;
        case 0xBCB9:
            func_BCB9_b6(); break;
        case 0x948B:
            func_948B_b6(); break;
        case 0xB095:
            func_B095_b6(); break;
        case 0xB8B1:
            func_B8B1_b6(); break;
        case 0xBC79:
            func_BC79_b6(); break;
        case 0x868D:
            func_868D_b6(); break;
        case 0xB200:
            switch (g_current_bank) {
                case 6: func_B200_b6(); break;
                case 7: func_B200_b7(); break;
                case 8: func_B200_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAFFC:
            switch (g_current_bank) {
                case 6: func_AFFC_b6(); break;
                case 5: func_AFFC_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9601:
            func_9601_b7(); break;
        case 0x9610:
            func_9610_b7(); break;
        case 0xB610:
            func_B610_b7(); break;
        case 0x80F1:
            switch (g_current_bank) {
                case 7: func_80F1_b7(); break;
                case 8: func_80F1_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB4F7:
            func_B4F7_b7(); break;
        case 0x9091:
            func_9091_b7(); break;
        case 0xAF70:
            func_AF70_b7(); break;
        case 0xBD5F:
            func_BD5F_b7(); break;
        case 0x96B1:
            switch (g_current_bank) {
                case 15: func_D6B1(); break;
                case 7: func_96B1_b7(); break;
                case 8: func_96B1_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8779:
            func_8779_b7(); break;
        case 0x9C1D:
            func_9C1D_b7(); break;
        case 0x9031:
            switch (g_current_bank) {
                case 15: func_D031(); break;
                case 7: func_9031_b7(); break;
                case 8: func_9031_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBBF6:
            func_BBF6_b7(); break;
        case 0x92EB:
            func_92EB_b7(); break;
        case 0x9293:
            func_9293_b7(); break;
        case 0x9093:
            func_9093_b7(); break;
        case 0x885D:
            func_885D_b7(); break;
        case 0xAAA3:
            func_AAA3_b7(); break;
        case 0xA5FE:
            func_A5FE_b7(); break;
        case 0x80D1:
            switch (g_current_bank) {
                case 7: func_80D1_b7(); break;
                case 2: func_80D1_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9006:
            switch (g_current_bank) {
                case 7: func_9006_b7(); break;
                case 14: func_9006_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x98CE:
            func_98CE_b7(); break;
        case 0x983D:
            func_983D_b7(); break;
        case 0xBCCF:
            func_BCCF_b7(); break;
        case 0x8409:
            switch (g_current_bank) {
                case 7: func_8409_b7(); break;
                case 11: func_8409_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x83B6:
            func_83B6_b7(); break;
        case 0xBEFF:
            switch (g_current_bank) {
                case 7: func_BEFF_b7(); break;
                case 8: func_BEFF_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8316:
            func_8316_b7(); break;
        case 0x811A:
            func_811A_b7(); break;
        case 0x911A:
            func_911A_b7(); break;
        case 0xA51A:
            func_A51A_b7(); break;
        case 0xB51A:
            func_B51A_b7(); break;
        case 0x8326:
            func_8326_b7(); break;
        case 0xAF26:
            func_AF26_b7(); break;
        case 0x8F1B:
            func_8F1B_b7(); break;
        case 0xA71B:
            func_A71B_b7(); break;
        case 0xBF28:
            func_BF28_b7(); break;
        case 0xAD29:
            func_AD29_b7(); break;
        case 0x8709:
            func_8709_b7(); break;
        case 0x8741:
            func_8741_b7(); break;
        case 0x8088:
            switch (g_current_bank) {
                case 15: func_C088(); break;
                case 7: func_8088_b7(); break;
                case 14: func_8088_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8881:
            switch (g_current_bank) {
                case 15: func_C881(); break;
                case 7: func_8881_b7(); break;
                case 8: func_8881_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x830B:
            func_830B_b7(); break;
        case 0x8309:
            func_8309_b7(); break;
        case 0x8052:
            func_8052_b7(); break;
        case 0x8054:
            func_8054_b7(); break;
        case 0x8149:
            func_8149_b7(); break;
        case 0x807B:
            func_807B_b7(); break;
        case 0x8067:
            func_8067_b7(); break;
        case 0xA12C:
            func_A12C_b7(); break;
        case 0xB52C:
            func_B52C_b7(); break;
        case 0x912D:
            func_912D_b7(); break;
        case 0xA530:
            func_A530_b7(); break;
        case 0xAE00:
            func_AE00_b7(); break;
        case 0x9200:
            func_9200_b7(); break;
        case 0xBFF0:
            switch (g_current_bank) {
                case 7: func_BFF0_b7(); break;
                case 8: func_BFF0_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBAE0:
            func_BAE0_b7(); break;
        case 0x8700:
            switch (g_current_bank) {
                case 7: func_8700_b7(); break;
                case 2: func_8700_b2(); break;
                case 6: func_8700_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB4F0:
            func_B4F0_b7(); break;
        case 0xBDFE:
            func_BDFE_b7(); break;
        case 0xBFD8:
            func_BFD8_b7(); break;
        case 0x85C0:
            func_85C0_b7(); break;
        case 0xB5F0:
            func_B5F0_b7(); break;
        case 0xBF02:
            func_BF02_b8(); break;
        case 0x9E02:
            switch (g_current_bank) {
                case 8: func_9E02_b8(); break;
                case 10: func_9E02_b10(); break;
                case 14: func_9E02_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x80E1:
            func_80E1_b8(); break;
        case 0x80A1:
            switch (g_current_bank) {
                case 15: func_C0A1(); break;
                case 8: func_80A1_b8(); break;
                case 12: func_80A1_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9F4A:
            func_9F4A_b8(); break;
        case 0x8F1E:
            func_8F1E_b8(); break;
        case 0x8DC3:
            func_8DC3_b8(); break;
        case 0xA0F9:
            switch (g_current_bank) {
                case 8: func_A0F9_b8(); break;
                case 10: func_A0F9_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8099:
            func_8099_b8(); break;
        case 0xAFD8:
            func_AFD8_b8(); break;
        case 0x8635:
            func_8635_b8(); break;
        case 0xB4FF:
            func_B4FF_b8(); break;
        case 0x9354:
            func_9354_b8(); break;
        case 0xBC9A:
            func_BC9A_b8(); break;
        case 0xBFA0:
            func_BFA0_b8(); break;
        case 0x8C31:
            switch (g_current_bank) {
                case 8: func_8C31_b8(); break;
                case 11: func_8C31_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9BC7:
            func_9BC7_b8(); break;
        case 0xB21E:
            func_B21E_b8(); break;
        case 0x9C9C:
            func_9C9C_b8(); break;
        case 0x9D9D:
            func_9D9D_b8(); break;
        case 0xAEAE:
            func_AEAE_b8(); break;
        case 0xB8B8:
            func_B8B8_b8(); break;
        case 0xBABA:
            func_BABA_b8(); break;
        case 0xBC78:
            func_BC78_b8(); break;
        case 0x8027:
            func_8027_b8(); break;
        case 0xBB20:
            func_BB20_b8(); break;
        case 0x9A9C:
            func_9A9C_b8(); break;
        case 0x8FCD:
            func_8FCD_b8(); break;
        case 0x80E5:
            func_80E5_b8(); break;
        case 0xBDA2:
            func_BDA2_b8(); break;
        case 0xB98E:
            switch (g_current_bank) {
                case 8: func_B98E_b8(); break;
                case 14: func_B98E_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBFBA:
            func_BFBA_b8(); break;
        case 0x9309:
            func_9309_b8(); break;
        case 0x9F20:
            func_9F20_b8(); break;
        case 0x9FC0:
            func_9FC0_b8(); break;
        case 0xB090:
            func_B090_b8(); break;
        case 0x8701:
            switch (g_current_bank) {
                case 15: func_C701(); break;
                case 8: func_8701_b8(); break;
                case 12: func_8701_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9F80:
            func_9F80_b8(); break;
        case 0x80ED:
            func_80ED_b8(); break;
        case 0xA7D0:
            func_A7D0_b8(); break;
        case 0x9F3F:
            func_9F3F_b8(); break;
        case 0xB382:
            func_B382_b8(); break;
        case 0xBB10:
            func_BB10_b8(); break;
        case 0x8172:
            switch (g_current_bank) {
                case 8: func_8172_b8(); break;
                case 12: func_8172_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8CB2:
            func_8CB2_b8(); break;
        case 0x8C39:
            switch (g_current_bank) {
                case 8: func_8C39_b8(); break;
                case 11: func_8C39_b11(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB910:
            switch (g_current_bank) {
                case 8: func_B910_b8(); break;
                case 14: func_B910_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9EA0:
            func_9EA0_b8(); break;
        case 0x819F:
            func_819F_b8(); break;
        case 0x8AE1:
            func_8AE1_b8(); break;
        case 0x9AB2:
            func_9AB2_b8(); break;
        case 0x9D99:
            switch (g_current_bank) {
                case 8: func_9D99_b8(); break;
                case 14: func_9D99_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8B74:
            func_8B74_b8(); break;
        case 0x9CAC:
            func_9CAC_b8(); break;
        case 0x8FD0:
            func_8FD0_b8(); break;
        case 0xB7B8:
            func_B7B8_b8(); break;
        case 0x8984:
            func_8984_b8(); break;
        case 0x83F6:
            func_83F6_b8(); break;
        case 0x8142:
            func_8142_b8(); break;
        case 0x9D80:
            func_9D80_b8(); break;
        case 0x9350:
            switch (g_current_bank) {
                case 8: func_9350_b8(); break;
                case 0: func_9350_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA094:
            func_A094_b8(); break;
        case 0xA100:
            func_A100_b8(); break;
        case 0xBF20:
            func_BF20_b8(); break;
        case 0x972B:
            func_972B_b8(); break;
        case 0xAB5C:
            func_AB5C_b8(); break;
        case 0x8C01:
            func_8C01_b8(); break;
        case 0x97E0:
            func_97E0_b8(); break;
        case 0x9BF0:
            func_9BF0_b8(); break;
        case 0xB100:
            func_B100_b8(); break;
        case 0x9EFE:
            func_9EFE_b8(); break;
        case 0xBD80:
            func_BD80_b8(); break;
        case 0xBF2A:
            switch (g_current_bank) {
                case 8: func_BF2A_b8(); break;
                case 4: func_BF2A_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBDFF:
            func_BDFF_b8(); break;
        case 0xBFF6:
            func_BFF6_b8(); break;
        case 0x8B0D:
            func_8B0D_b10(); break;
        case 0xB2C7:
            func_B2C7_b10(); break;
        case 0x846C:
            func_846C_b10(); break;
        case 0x82C1:
            func_82C1_b10(); break;
        case 0xA348:
            switch (g_current_bank) {
                case 10: func_A348_b10(); break;
                case 14: func_A348_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x91A4:
            func_91A4_b10(); break;
        case 0x9792:
            func_9792_b10(); break;
        case 0x9A33:
            func_9A33_b10(); break;
        case 0xA62D:
            func_A62D_b10(); break;
        case 0xAE5F:
            func_AE5F_b10(); break;
        case 0xAEF4:
            func_AEF4_b10(); break;
        case 0x92DD:
            func_92DD_b10(); break;
        case 0x8036:
            func_8036_b10(); break;
        case 0xA26B:
            switch (g_current_bank) {
                case 10: func_A26B_b10(); break;
                case 14: func_A26B_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xACD5:
            func_ACD5_b10(); break;
        case 0xA059:
            func_A059_b10(); break;
        case 0x86C7:
            func_86C7_b10(); break;
        case 0x8F90:
            func_8F90_b10(); break;
        case 0x90C8:
            func_90C8_b10(); break;
        case 0xA2E7:
            switch (g_current_bank) {
                case 10: func_A2E7_b10(); break;
                case 14: func_A2E7_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9082:
            func_9082_b10(); break;
        case 0x9F10:
            func_9F10_b10(); break;
        case 0xA308:
            func_A308_b10(); break;
        case 0x8387:
            switch (g_current_bank) {
                case 15: func_C387(); break;
                case 10: func_8387_b10(); break;
                case 12: func_8387_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C87:
            func_8C87_b10(); break;
        case 0x8F08:
            func_8F08_b10(); break;
        case 0x8F1A:
            func_8F1A_b10(); break;
        case 0xAA40:
            func_AA40_b10(); break;
        case 0xA453:
            func_A453_b10(); break;
        case 0xAE1B:
            switch (g_current_bank) {
                case 10: func_AE1B_b10(); break;
                case 14: func_AE1B_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB4CB:
            func_B4CB_b10(); break;
        case 0x8D16:
            func_8D16_b10(); break;
        case 0xAA11:
            func_AA11_b10(); break;
        case 0x8C8F:
            func_8C8F_b10(); break;
        case 0xAA56:
            func_AA56_b10(); break;
        case 0x9CE4:
            func_9CE4_b10(); break;
        case 0xAA70:
            func_AA70_b10(); break;
        case 0x8C0D:
            func_8C0D_b10(); break;
        case 0x8B34:
            func_8B34_b10(); break;
        case 0x8714:
            func_8714_b10(); break;
        case 0x93AE:
            switch (g_current_bank) {
                case 10: func_93AE_b10(); break;
                case 14: func_93AE_b14(); break;
                case 5: func_93AE_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8A94:
            func_8A94_b10(); break;
        case 0x8441:
            func_8441_b10(); break;
        case 0x8287:
            switch (g_current_bank) {
                case 10: func_8287_b10(); break;
                case 3: func_8287_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9455:
            func_9455_b10(); break;
        case 0xA8D1:
            func_A8D1_b10(); break;
        case 0x9291:
            func_9291_b10(); break;
        case 0xA425:
            func_A425_b10(); break;
        case 0x8E88:
            switch (g_current_bank) {
                case 10: func_8E88_b10(); break;
                case 5: func_8E88_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9877:
            func_9877_b10(); break;
        case 0xAB80:
            func_AB80_b10(); break;
        case 0x8020:
            func_8020_b10(); break;
        case 0x864F:
            func_864F_b10(); break;
        case 0xAF60:
            func_AF60_b10(); break;
        case 0xA881:
            func_A881_b10(); break;
        case 0xA491:
            switch (g_current_bank) {
                case 10: func_A491_b10(); break;
                case 12: func_A491_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x88B4:
            func_88B4_b10(); break;
        case 0xAB60:
            func_AB60_b10(); break;
        case 0xA903:
            switch (g_current_bank) {
                case 10: func_A903_b10(); break;
                case 12: func_A903_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAAE0:
            func_AAE0_b10(); break;
        case 0xA843:
            func_A843_b10(); break;
        case 0xB4CF:
            func_B4CF_b10(); break;
        case 0x9F70:
            func_9F70_b10(); break;
        case 0x85D7:
            func_85D7_b10(); break;
        case 0x8F68:
            func_8F68_b10(); break;
        case 0x9192:
            func_9192_b10(); break;
        case 0x8092:
            func_8092_b10(); break;
        case 0xA6B5:
            func_A6B5_b10(); break;
        case 0x98E2:
            func_98E2_b10(); break;
        case 0x949A:
            func_949A_b10(); break;
        case 0x9997:
            func_9997_b10(); break;
        case 0x91A7:
            func_91A7_b10(); break;
        case 0x809C:
            func_809C_b10(); break;
        case 0xA8EF:
            func_A8EF_b10(); break;
        case 0x80BC:
            func_80BC_b10(); break;
        case 0xA7DC:
            func_A7DC_b10(); break;
        case 0x9898:
            func_9898_b10(); break;
        case 0x86F9:
            func_86F9_b10(); break;
        case 0xA7F4:
            func_A7F4_b10(); break;
        case 0x8CDA:
            func_8CDA_b10(); break;
        case 0x819B:
            func_819B_b10(); break;
        case 0x8FB5:
            func_8FB5_b10(); break;
        case 0xA6AB:
            func_A6AB_b10(); break;
        case 0x8AFA:
            func_8AFA_b10(); break;
        case 0x85F4:
            func_85F4_b10(); break;
        case 0x8585:
            func_8585_b10(); break;
        case 0x8686:
            switch (g_current_bank) {
                case 10: func_8686_b10(); break;
                case 12: func_8686_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8247:
            func_8247_b11(); break;
        case 0x8258:
            func_8258_b11(); break;
        case 0x82F3:
            func_82F3_b11(); break;
        case 0x8348:
            func_8348_b11(); break;
        case 0x834C:
            func_834C_b11(); break;
        case 0x8350:
            func_8350_b11(); break;
        case 0x8368:
            func_8368_b11(); break;
        case 0x8B84:
            func_8B84_b11(); break;
        case 0x838C:
            func_838C_b11(); break;
        case 0x83BA:
            func_83BA_b11(); break;
        case 0x83C8:
            func_83C8_b11(); break;
        case 0x83F1:
            func_83F1_b11(); break;
        case 0x841F:
            switch (g_current_bank) {
                case 11: func_841F_b11(); break;
                case 5: func_841F_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8425:
            func_8425_b11(); break;
        case 0x842B:
            func_842B_b11(); break;
        case 0x8437:
            func_8437_b11(); break;
        case 0x8457:
            func_8457_b11(); break;
        case 0x8463:
            func_8463_b11(); break;
        case 0x846B:
            func_846B_b11(); break;
        case 0x83E3:
            func_83E3_b11(); break;
        case 0x83EA:
            func_83EA_b11(); break;
        case 0x8A30:
            func_8A30_b11(); break;
        case 0x8529:
            switch (g_current_bank) {
                case 11: func_8529_b11(); break;
                case 14: func_8529_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8539:
            func_8539_b11(); break;
        case 0x853F:
            func_853F_b11(); break;
        case 0x8547:
            func_8547_b11(); break;
        case 0x8559:
            func_8559_b11(); break;
        case 0x855F:
            func_855F_b11(); break;
        case 0x8567:
            func_8567_b11(); break;
        case 0x8571:
            func_8571_b11(); break;
        case 0x8591:
            func_8591_b11(); break;
        case 0x85C3:
            func_85C3_b11(); break;
        case 0x85D9:
            func_85D9_b11(); break;
        case 0x8605:
            func_8605_b11(); break;
        case 0x8613:
            func_8613_b11(); break;
        case 0x861D:
            func_861D_b11(); break;
        case 0x8643:
            func_8643_b11(); break;
        case 0x8711:
            func_8711_b11(); break;
        case 0x8717:
            func_8717_b11(); break;
        case 0x8923:
            func_8923_b11(); break;
        case 0x8B08:
            switch (g_current_bank) {
                case 11: func_8B08_b11(); break;
                case 5: func_8B08_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x87CB:
            func_87CB_b11(); break;
        case 0x87E7:
            func_87E7_b11(); break;
        case 0x8859:
            func_8859_b11(); break;
        case 0x8863:
            func_8863_b11(); break;
        case 0x8867:
            func_8867_b11(); break;
        case 0x8B21:
            func_8B21_b11(); break;
        case 0x88E9:
            func_88E9_b11(); break;
        case 0x8911:
            func_8911_b11(); break;
        case 0x8921:
            func_8921_b11(); break;
        case 0x8979:
            func_8979_b11(); break;
        case 0x8981:
            func_8981_b11(); break;
        case 0x899D:
            func_899D_b11(); break;
        case 0x89F9:
            func_89F9_b11(); break;
        case 0x8A5D:
            func_8A5D_b11(); break;
        case 0x8A6F:
            func_8A6F_b11(); break;
        case 0x8B15:
            func_8B15_b11(); break;
        case 0x8B1F:
            switch (g_current_bank) {
                case 11: func_8B1F_b11(); break;
                case 5: func_8B1F_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8B33:
            func_8B33_b11(); break;
        case 0x8B4D:
            func_8B4D_b11(); break;
        case 0x8B6C:
            func_8B6C_b11(); break;
        case 0x8B92:
            func_8B92_b11(); break;
        case 0x8B97:
            func_8B97_b11(); break;
        case 0x8BA7:
            func_8BA7_b11(); break;
        case 0x8BC8:
            func_8BC8_b11(); break;
        case 0x8BD7:
            func_8BD7_b11(); break;
        case 0x8BE4:
            func_8BE4_b11(); break;
        case 0x8BF1:
            func_8BF1_b11(); break;
        case 0x8C12:
            switch (g_current_bank) {
                case 11: func_8C12_b11(); break;
                case 2: func_8C12_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8C4B:
            func_8C4B_b11(); break;
        case 0x8C4F:
            func_8C4F_b11(); break;
        case 0x8C6F:
            func_8C6F_b11(); break;
        case 0x8744:
            func_8744_b11(); break;
        case 0x841A:
            func_841A_b11(); break;
        case 0x8421:
            func_8421_b11(); break;
        case 0xACBA:
            func_ACBA_b12(); break;
        case 0xACAC:
            func_ACAC_b12(); break;
        case 0x9F9F:
            func_9F9F_b12(); break;
        case 0xA1A1:
            func_A1A1_b12(); break;
        case 0xA4A4:
            func_A4A4_b12(); break;
        case 0x9393:
            func_9393_b12(); break;
        case 0x8989:
            func_8989_b12(); break;
        case 0x9595:
            func_9595_b12(); break;
        case 0x9696:
            func_9696_b12(); break;
        case 0x9797:
            func_9797_b12(); break;
        case 0x8399:
            switch (g_current_bank) {
                case 12: func_8399_b12(); break;
                case 2: func_8399_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9A84:
            func_9A84_b12(); break;
        case 0xAD03:
            func_AD03_b12(); break;
        case 0xA507:
            func_A507_b12(); break;
        case 0xA991:
            func_A991_b12(); break;
        case 0x8D0F:
            func_8D0F_b12(); break;
        case 0x8619:
            func_8619_b12(); break;
        case 0xA228:
            func_A228_b12(); break;
        case 0x827C:
            func_827C_b12(); break;
        case 0x82AB:
            func_82AB_b12(); break;
        case 0x8586:
            switch (g_current_bank) {
                case 12: func_8586_b12(); break;
                case 3: func_8586_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8121:
            func_8121_b12(); break;
        case 0x9088:
            func_9088_b12(); break;
        case 0xA983:
            func_A983_b12(); break;
        case 0x86E9:
            func_86E9_b12(); break;
        case 0xA59A:
            func_A59A_b12(); break;
        case 0x9085:
            switch (g_current_bank) {
                case 12: func_9085_b12(); break;
                case 0: func_9085_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x81CA:
            func_81CA_b12(); break;
        case 0x8ACA:
            func_8ACA_b12(); break;
        case 0x8521:
            func_8521_b12(); break;
        case 0x8DEE:
            func_8DEE_b12(); break;
        case 0xA985:
            func_A985_b12(); break;
        case 0x84E6:
            func_84E6_b12(); break;
        case 0x88D9:
            func_88D9_b12(); break;
        case 0x8061:
            func_8061_b12(); break;
        case 0xA561:
            func_A561_b12(); break;
        case 0xA583:
            func_A583_b12(); break;
        case 0x8569:
            func_8569_b12(); break;
        case 0x9D03:
            func_9D03_b12(); break;
        case 0x88A9:
            switch (g_current_bank) {
                case 15: func_C8A9(); break;
                case 12: func_88A9_b12(); break;
                case 14: func_88A9_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA440:
            func_A440_b12(); break;
        case 0xA50A:
            switch (g_current_bank) {
                case 12: func_A50A_b12(); break;
                case 4: func_A50A_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAD0D:
            switch (g_current_bank) {
                case 12: func_AD0D_b12(); break;
                case 14: func_AD0D_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x85F9:
            func_85F9_b12(); break;
        case 0xA5AB:
            func_A5AB_b12(); break;
        case 0x8589:
            func_8589_b12(); break;
        case 0xA2EE:
            func_A2EE_b12(); break;
        case 0x8D05:
            func_8D05_b12(); break;
        case 0x99ED:
            func_99ED_b12(); break;
        case 0x8D53:
            func_8D53_b12(); break;
        case 0x8D11:
            func_8D11_b12(); break;
        case 0x85D4:
            func_85D4_b12(); break;
        case 0x850C:
            func_850C_b12(); break;
        case 0x8E64:
            func_8E64_b12(); break;
        case 0x8091:
            func_8091_b12(); break;
        case 0x9284:
            switch (g_current_bank) {
                case 12: func_9284_b12(); break;
                case 14: func_9284_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9494:
            func_9494_b12(); break;
        case 0xA80B:
            func_A80B_b12(); break;
        case 0x85ED:
            func_85ED_b12(); break;
        case 0xA961:
            func_A961_b12(); break;
        case 0xACF9:
            func_ACF9_b12(); break;
        case 0x8889:
            func_8889_b12(); break;
        case 0x85C1:
            func_85C1_b12(); break;
        case 0x8524:
            func_8524_b12(); break;
        case 0x914D:
            switch (g_current_bank) {
                case 12: func_914D_b12(); break;
                case 14: func_914D_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x88F9:
            func_88F9_b12(); break;
        case 0x8511:
            func_8511_b12(); break;
        case 0xA021:
            func_A021_b12(); break;
        case 0xA0F4:
            func_A0F4_b12(); break;
        case 0x9205:
            switch (g_current_bank) {
                case 12: func_9205_b12(); break;
                case 0: func_9205_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9993:
            func_9993_b12(); break;
        case 0xA9FD:
            func_A9FD_b12(); break;
        case 0xA0FD:
            func_A0FD_b12(); break;
        case 0x8D93:
            func_8D93_b12(); break;
        case 0xA2C1:
            func_A2C1_b12(); break;
        case 0x8592:
            switch (g_current_bank) {
                case 12: func_8592_b12(); break;
                case 0: func_8592_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9095:
            func_9095_b12(); break;
        case 0xA592:
            func_A592_b12(); break;
        case 0x86FA:
            func_86FA_b12(); break;
        case 0xA522:
            func_A522_b12(); break;
        case 0x8D69:
            func_8D69_b12(); break;
        case 0x8F00:
            func_8F00_b12(); break;
        case 0x948E:
            switch (g_current_bank) {
                case 15: func_D48E(); break;
                case 12: func_948E_b12(); break;
                case 14: func_948E_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8D97:
            func_8D97_b12(); break;
        case 0xA204:
            func_A204_b12(); break;
        case 0x8D32:
            func_8D32_b12(); break;
        case 0xA297:
            func_A297_b12(); break;
        case 0xA721:
            func_A721_b12(); break;
        case 0x8EF9:
            func_8EF9_b12(); break;
        case 0xACEF:
            func_ACEF_b12(); break;
        case 0xA299:
            func_A299_b12(); break;
        case 0xA0F6:
            switch (g_current_bank) {
                case 12: func_A0F6_b12(); break;
                case 14: func_A0F6_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA90B:
            func_A90B_b12(); break;
        case 0xA811:
            func_A811_b12(); break;
        case 0x8E6A:
            func_8E6A_b12(); break;
        case 0x88ED:
            func_88ED_b12(); break;
        case 0x9189:
            func_9189_b12(); break;
        case 0x8D9B:
            func_8D9B_b12(); break;
        case 0x8095:
            func_8095_b12(); break;
        case 0x9AE6:
            func_9AE6_b12(); break;
        case 0x9ADE:
            func_9ADE_b12(); break;
        case 0xA504:
            func_A504_b12(); break;
        case 0xA5A2:
            func_A5A2_b12(); break;
        case 0xA2EA:
            func_A2EA_b12(); break;
        case 0x8583:
            func_8583_b12(); break;
        case 0x85CD:
            func_85CD_b12(); break;
        case 0x8D24:
            func_8D24_b12(); break;
        case 0xA2D1:
            func_A2D1_b12(); break;
        case 0x9DAE:
            func_9DAE_b12(); break;
        case 0x8C52:
            func_8C52_b12(); break;
        case 0x9FAF:
            func_9FAF_b12(); break;
        case 0x807D:
            func_807D_b12(); break;
        case 0x8481:
            func_8481_b12(); break;
        case 0xA4A1:
            func_A4A1_b12(); break;
        case 0xA0C5:
            func_A0C5_b12(); break;
        case 0xA3A4:
            func_A3A4_b12(); break;
        case 0xA3A2:
            func_A3A2_b12(); break;
        case 0xA5A7:
            func_A5A7_b12(); break;
        case 0xA4A6:
            func_A4A6_b12(); break;
        case 0xA0AB:
            func_A0AB_b12(); break;
        case 0xA0C7:
            func_A0C7_b12(); break;
        case 0xA0DB:
            func_A0DB_b12(); break;
        case 0xA11F:
            func_A11F_b12(); break;
        case 0xA12A:
            func_A12A_b12(); break;
        case 0xA144:
            func_A144_b12(); break;
        case 0xA14F:
            func_A14F_b12(); break;
        case 0xA16B:
            func_A16B_b12(); break;
        case 0xA193:
            func_A193_b12(); break;
        case 0x8813:
            func_8813_b12(); break;
        case 0xA1A9:
            func_A1A9_b12(); break;
        case 0xA1CE:
            func_A1CE_b12(); break;
        case 0xA1E2:
            func_A1E2_b12(); break;
        case 0xA1F8:
            func_A1F8_b12(); break;
        case 0xA20E:
            func_A20E_b12(); break;
        case 0xA23A:
            func_A23A_b12(); break;
        case 0xA264:
            func_A264_b12(); break;
        case 0xA26F:
            func_A26F_b12(); break;
        case 0xA285:
            func_A285_b12(); break;
        case 0xA303:
            func_A303_b12(); break;
        case 0xA2AF:
            switch (g_current_bank) {
                case 12: func_A2AF_b12(); break;
                case 14: func_A2AF_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8404:
            func_8404_b12(); break;
        case 0xA2B6:
            func_A2B6_b12(); break;
        case 0xA2CC:
            func_A2CC_b12(); break;
        case 0xA2D7:
            func_A2D7_b12(); break;
        case 0xA2E2:
            func_A2E2_b12(); break;
        case 0xA2F8:
            func_A2F8_b12(); break;
        case 0x9304:
            func_9304_b12(); break;
        case 0xA30E:
            func_A30E_b12(); break;
        case 0x9804:
            func_9804_b12(); break;
        case 0xA319:
            func_A319_b12(); break;
        case 0x9A04:
            func_9A04_b12(); break;
        case 0xA33A:
            func_A33A_b12(); break;
        case 0xA104:
            func_A104_b12(); break;
        case 0x8308:
            switch (g_current_bank) {
                case 12: func_8308_b12(); break;
                case 7: func_8308_b7(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA35B:
            func_A35B_b12(); break;
        case 0xA378:
            func_A378_b12(); break;
        case 0xA449:
            func_A449_b12(); break;
        case 0xA46D:
            func_A46D_b12(); break;
        case 0xA47A:
            func_A47A_b12(); break;
        case 0x9012:
            func_9012_b12(); break;
        case 0x9A12:
            func_9A12_b12(); break;
        case 0xA49B:
            func_A49B_b12(); break;
        case 0x9A09:
            func_9A09_b12(); break;
        case 0x8915:
            func_8915_b12(); break;
        case 0x9016:
            func_9016_b12(); break;
        case 0x9606:
            func_9606_b12(); break;
        case 0xA57F:
            func_A57F_b12(); break;
        case 0x9709:
            func_9709_b12(); break;
        case 0x9E09:
            func_9E09_b12(); break;
        case 0x8600:
            func_8600_b12(); break;
        case 0xA602:
            func_A602_b12(); break;
        case 0xA702:
            func_A702_b12(); break;
        case 0x85A5:
            func_85A5_b12(); break;
        case 0xA0A9:
            func_A0A9_b12(); break;
        case 0x8DA9:
            func_8DA9_b12(); break;
        case 0xA86B:
            func_A86B_b12(); break;
        case 0xA86F:
            func_A86F_b12(); break;
        case 0x8F8E:
            func_8F8E_b12(); break;
        case 0x8E6E:
            func_8E6E_b12(); break;
        case 0xACAA:
            func_ACAA_b12(); break;
        case 0xAD17:
            func_AD17_b12(); break;
        case 0x8CEF:
            func_8CEF_b12(); break;
        case 0x9C21:
            switch (g_current_bank) {
                case 12: func_9C21_b12(); break;
                case 14: func_9C21_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA9EB:
            func_A9EB_b12(); break;
        case 0xA221:
            func_A221_b12(); break;
        case 0x949E:
            func_949E_b12(); break;
        case 0x969E:
            func_969E_b12(); break;
        case 0xA997:
            switch (g_current_bank) {
                case 12: func_A997_b12(); break;
                case 14: func_A997_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9D20:
            func_9D20_b12(); break;
        case 0xAD08:
            switch (g_current_bank) {
                case 12: func_AD08_b12(); break;
                case 0: func_AD08_b0(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAD2E:
            switch (g_current_bank) {
                case 12: func_AD2E_b12(); break;
                case 14: func_AD2E_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9DEB:
            func_9DEB_b12(); break;
        case 0x8200:
            func_8200_b12(); break;
        case 0x8E02:
            func_8E02_b12(); break;
        case 0x92D7:
            func_92D7_b13(); break;
        case 0x9ADB:
            func_9ADB_b13(); break;
        case 0x80C1:
            func_80C1_b13(); break;
        case 0xA92A:
            func_A92A_b13(); break;
        case 0x828B:
            func_828B_b14(); break;
        case 0x9E93:
            func_9E93_b14(); break;
        case 0x947D:
            switch (g_current_bank) {
                case 14: func_947D_b14(); break;
                case 6: func_947D_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9C7B:
            func_9C7B_b14(); break;
        case 0xA28A:
            func_A28A_b14(); break;
        case 0x8CA3:
            func_8CA3_b14(); break;
        case 0x9FA3:
            func_9FA3_b14(); break;
        case 0xA2D8:
            func_A2D8_b14(); break;
        case 0xA937:
            func_A937_b14(); break;
        case 0x9E00:
            func_9E00_b14(); break;
        case 0xBCD1:
            func_BCD1_b14(); break;
        case 0xAD34:
            func_AD34_b14(); break;
        case 0x83AE:
            func_83AE_b14(); break;
        case 0xA9F6:
            func_A9F6_b14(); break;
        case 0x8E21:
            func_8E21_b14(); break;
        case 0xAE8D:
            func_AE8D_b14(); break;
        case 0xA929:
            func_A929_b14(); break;
        case 0xA934:
            func_A934_b14(); break;
        case 0xBD34:
            func_BD34_b14(); break;
        case 0x82F1:
            func_82F1_b14(); break;
        case 0x9EE6:
            func_9EE6_b14(); break;
        case 0xBD8E:
            func_BD8E_b14(); break;
        case 0xAD04:
            func_AD04_b14(); break;
        case 0xBCAE:
            func_BCAE_b14(); break;
        case 0x8DFA:
            func_8DFA_b14(); break;
        case 0xBD03:
            func_BD03_b14(); break;
        case 0x9A21:
            func_9A21_b14(); break;
        case 0x9EC6:
            switch (g_current_bank) {
                case 14: func_9EC6_b14(); break;
                case 4: func_9EC6_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA04D:
            switch (g_current_bank) {
                case 14: func_A04D_b14(); break;
                case 2: func_A04D_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBD13:
            func_BD13_b14(); break;
        case 0xBC9E:
            func_BC9E_b14(); break;
        case 0xBD49:
            func_BD49_b14(); break;
        case 0xB7A6:
            func_B7A6_b14(); break;
        case 0xB5A9:
            func_B5A9_b14(); break;
        case 0xBC10:
            func_BC10_b14(); break;
        case 0xAE61:
            func_AE61_b14(); break;
        case 0x8587:
            switch (g_current_bank) {
                case 14: func_8587_b14(); break;
                case 2: func_8587_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB786:
            func_B786_b14(); break;
        case 0xAE10:
            func_AE10_b14(); break;
        case 0xAE0E:
            func_AE0E_b14(); break;
        case 0xA217:
            func_A217_b14(); break;
        case 0xAE0A:
            func_AE0A_b14(); break;
        case 0x9EA6:
            func_9EA6_b14(); break;
        case 0x85F2:
            func_85F2_b14(); break;
        case 0xA5BA:
            func_A5BA_b14(); break;
        case 0x8A0F:
            switch (g_current_bank) {
                case 14: func_8A0F_b14(); break;
                case 5: func_8A0F_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAE3E:
            func_AE3E_b14(); break;
        case 0x9BAE:
            func_9BAE_b14(); break;
        case 0x8510:
            func_8510_b14(); break;
        case 0x884B:
            func_884B_b14(); break;
        case 0xAEB2:
            func_AEB2_b14(); break;
        case 0x8DBB:
            func_8DBB_b14(); break;
        case 0x9089:
            func_9089_b14(); break;
        case 0xA5D1:
            func_A5D1_b14(); break;
        case 0xA486:
            func_A486_b14(); break;
        case 0x84C9:
            func_84C9_b14(); break;
        case 0xBD2B:
            func_BD2B_b14(); break;
        case 0xBC8C:
            func_BC8C_b14(); break;
        case 0xB916:
            func_B916_b14(); break;
        case 0xAD80:
            func_AD80_b14(); break;
        case 0x851C:
            func_851C_b14(); break;
        case 0xB949:
            func_B949_b14(); break;
        case 0x8968:
            func_8968_b14(); break;
        case 0x897F:
            func_897F_b14(); break;
        case 0x9889:
            func_9889_b14(); break;
        case 0xAD8A:
            func_AD8A_b14(); break;
        case 0xA5A5:
            func_A5A5_b14(); break;
        case 0xBD8B:
            func_BD8B_b14(); break;
        case 0x8506:
            func_8506_b14(); break;
        case 0x8D06:
            func_8D06_b14(); break;
        case 0x858C:
            func_858C_b14(); break;
        case 0xAC57:
            func_AC57_b14(); break;
        case 0xB8AE:
            func_B8AE_b14(); break;
        case 0xAC37:
            func_AC37_b14(); break;
        case 0xBB11:
            func_BB11_b14(); break;
        case 0x9FA6:
            func_9FA6_b14(); break;
        case 0xA52C:
            func_A52C_b14(); break;
        case 0xA2A6:
            func_A2A6_b14(); break;
        case 0x87BA:
            func_87BA_b14(); break;
        case 0xB8A6:
            func_B8A6_b14(); break;
        case 0xA58D:
            func_A58D_b14(); break;
        case 0x85B9:
            func_85B9_b14(); break;
        case 0x8534:
            func_8534_b14(); break;
        case 0x8E3B:
            func_8E3B_b14(); break;
        case 0x858F:
            func_858F_b14(); break;
        case 0x8D8F:
            func_8D8F_b14(); break;
        case 0xA9A9:
            func_A9A9_b14(); break;
        case 0x8EB9:
            func_8EB9_b14(); break;
        case 0xAD84:
            func_AD84_b14(); break;
        case 0xA990:
            func_A990_b14(); break;
        case 0x9C4D:
            func_9C4D_b14(); break;
        case 0x9521:
            func_9521_b14(); break;
        case 0xB0BB:
            func_B0BB_b14(); break;
        case 0xA508:
            func_A508_b14(); break;
        case 0xA009:
            func_A009_b14(); break;
        case 0x9021:
            switch (g_current_bank) {
                case 15: func_D021(); break;
                case 14: func_9021_b14(); break;
                case 1: func_9021_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA010:
            func_A010_b14(); break;
        case 0x9009:
            func_9009_b14(); break;
        case 0xA893:
            func_A893_b14(); break;
        case 0xAD02:
            func_AD02_b14(); break;
        case 0x8832:
            func_8832_b14(); break;
        case 0xA9C3:
            func_A9C3_b14(); break;
        case 0x9E66:
            func_9E66_b14(); break;
        case 0x882F:
            func_882F_b14(); break;
        case 0x8598:
            func_8598_b14(); break;
        case 0xAABA:
            func_AABA_b14(); break;
        case 0xA5C9:
            func_A5C9_b14(); break;
        case 0x8817:
            func_8817_b14(); break;
        case 0xA029:
            func_A029_b14(); break;
        case 0xBD25:
            func_BD25_b14(); break;
        case 0xA84B:
            func_A84B_b14(); break;
        case 0xA09A:
            func_A09A_b14(); break;
        case 0xAED8:
            func_AED8_b14(); break;
        case 0x8D31:
            func_8D31_b14(); break;
        case 0xBD1B:
            func_BD1B_b14(); break;
        case 0xBD0A:
            func_BD0A_b14(); break;
        case 0xA908:
            func_A908_b14(); break;
        case 0xBC05:
            func_BC05_b14(); break;
        case 0x8803:
            func_8803_b14(); break;
        case 0xAD0A:
            func_AD0A_b14(); break;
        case 0x9003:
            switch (g_current_bank) {
                case 14: func_9003_b14(); break;
                case 12: func_9003_b12(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xBD10:
            func_BD10_b14(); break;
        case 0x864D:
            func_864D_b14(); break;
        case 0x8DA0:
            func_8DA0_b14(); break;
        case 0xBD31:
            func_BD31_b14(); break;
        case 0x900B:
            func_900B_b14(); break;
        case 0xAD2A:
            func_AD2A_b14(); break;
        case 0x9954:
            func_9954_b14(); break;
        case 0xA92B:
            func_A92B_b14(); break;
        case 0x8A8D:
            func_8A8D_b14(); break;
        case 0xAA0B:
            func_AA0B_b14(); break;
        case 0xAA69:
            func_AA69_b14(); break;
        case 0xA9A3:
            func_A9A3_b14(); break;
        case 0xAD1F:
            func_AD1F_b14(); break;
        case 0x90F0:
            switch (g_current_bank) {
                case 14: func_90F0_b14(); break;
                case 2: func_90F0_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xAE06:
            func_AE06_b14(); break;
        case 0xAD39:
            func_AD39_b14(); break;
        case 0x8AA9:
            func_8AA9_b14(); break;
        case 0xA6AE:
            func_A6AE_b14(); break;
        case 0xAD9C:
            func_AD9C_b14(); break;
        case 0x96A0:
            func_96A0_b14(); break;
        case 0x83A4:
            func_83A4_b14(); break;
        case 0x89A5:
            func_89A5_b14(); break;
        case 0xAD92:
            func_AD92_b14(); break;
        case 0x84C1:
            func_84C1_b14(); break;
        case 0xA910:
            func_A910_b14(); break;
        case 0xA0AA:
            func_A0AA_b14(); break;
        case 0xA5E8:
            func_A5E8_b14(); break;
        case 0xBC4D:
            func_BC4D_b14(); break;
        case 0xA9CB:
            func_A9CB_b14(); break;
        case 0x95BA:
            func_95BA_b14(); break;
        case 0x94BA:
            func_94BA_b14(); break;
        case 0xA795:
            func_A795_b14(); break;
        case 0x8407:
            func_8407_b14(); break;
        case 0xA7F6:
            func_A7F6_b14(); break;
        case 0x9D11:
            func_9D11_b14(); break;
        case 0x9DF0:
            func_9DF0_b14(); break;
        case 0xA016:
            func_A016_b14(); break;
        case 0xA032:
            func_A032_b14(); break;
        case 0xBC03:
            func_BC03_b14(); break;
        case 0xBC85:
            func_BC85_b14(); break;
        case 0xAA7D:
            func_AA7D_b14(); break;
        case 0xBD17:
            func_BD17_b14(); break;
        case 0xAAF7:
            func_AAF7_b14(); break;
        case 0xB67A:
            func_B67A_b14(); break;
        case 0xAC72:
            func_AC72_b14(); break;
        case 0x9EAD:
            func_9EAD_b14(); break;
        case 0xB0AD:
            func_B0AD_b14(); break;
        case 0x8079:
            func_8079_b14(); break;
        case 0xADF8:
            func_ADF8_b14(); break;
        case 0xAF3E:
            func_AF3E_b14(); break;
        case 0xACB0:
            func_ACB0_b14(); break;
        case 0xAF69:
            func_AF69_b14(); break;
        case 0xAF99:
            func_AF99_b14(); break;
        case 0xB020:
            func_B020_b14(); break;
        case 0xB049:
            switch (g_current_bank) {
                case 14: func_B049_b14(); break;
                case 6: func_B049_b6(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB07F:
            func_B07F_b14(); break;
        case 0x8CAE:
            func_8CAE_b14(); break;
        case 0xB069:
            func_B069_b14(); break;
        case 0xB0DC:
            func_B0DC_b14(); break;
        case 0xB174:
            func_B174_b14(); break;
        case 0xA6B2:
            func_A6B2_b14(); break;
        case 0xAE30:
            func_AE30_b14(); break;
        case 0xAE29:
            func_AE29_b14(); break;
        case 0xAE54:
            func_AE54_b14(); break;
        case 0xAE4D:
            func_AE4D_b14(); break;
        case 0xAE68:
            func_AE68_b14(); break;
        case 0x9A41:
            func_9A41_b14(); break;
        case 0xAE9B:
            func_AE9B_b14(); break;
        case 0xAE94:
            func_AE94_b14(); break;
        case 0x8C06:
            func_8C06_b14(); break;
        case 0xAEF9:
            func_AEF9_b14(); break;
        case 0xAEF2:
            func_AEF2_b14(); break;
        case 0xAF43:
            func_AF43_b14(); break;
        case 0xAF8F:
            func_AF8F_b14(); break;
        case 0xAFE6:
            func_AFE6_b14(); break;
        case 0xAFF6:
            func_AFF6_b14(); break;
        case 0xAFEC:
            func_AFEC_b14(); break;
        case 0xB012:
            func_B012_b14(); break;
        case 0xB008:
            func_B008_b14(); break;
        case 0xB0F6:
            func_B0F6_b14(); break;
        case 0xB0EE:
            func_B0EE_b14(); break;
        case 0x8051:
            func_8051_b14(); break;
        case 0xB188:
            func_B188_b14(); break;
        case 0xB181:
            func_B181_b14(); break;
        case 0xB190:
            func_B190_b14(); break;
        case 0xB197:
            func_B197_b14(); break;
        case 0x803D:
            switch (g_current_bank) {
                case 14: func_803D_b14(); break;
                case 3: func_803D_b3(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9FBE:
            func_9FBE_b14(); break;
        case 0xB8A0:
            func_B8A0_b14(); break;
        case 0x9FC6:
            func_9FC6_b14(); break;
        case 0xADBA:
            func_ADBA_b14(); break;
        case 0x85CF:
            func_85CF_b14(); break;
        case 0xA528:
            func_A528_b14(); break;
        case 0xA506:
            func_A506_b14(); break;
        case 0xA512:
            func_A512_b14(); break;
        case 0xB97C:
            func_B97C_b14(); break;
        case 0x8D09:
            func_8D09_b14(); break;
        case 0x8531:
            func_8531_b14(); break;
        case 0x924D:
            func_924D_b14(); break;
        case 0xB68E:
            func_B68E_b14(); break;
        case 0xAD49:
            func_AD49_b14(); break;
        case 0xBAF9:
            func_BAF9_b14(); break;
        case 0xBBF3:
            func_BBF3_b14(); break;
        case 0x98BB:
            func_98BB_b14(); break;
        case 0xBC99:
            func_BC99_b14(); break;
        case 0xBBEA:
            func_BBEA_b14(); break;
        case 0xA6C4:
            func_A6C4_b14(); break;
        case 0xB5C4:
            func_B5C4_b14(); break;
        case 0xB0BD:
            func_B0BD_b14(); break;
        case 0xB5AE:
            func_B5AE_b14(); break;
        case 0x9D7A:
            func_9D7A_b14(); break;
        case 0xB0B6:
            func_B0B6_b14(); break;
        case 0x8A61:
            func_8A61_b14(); break;
        case 0xAAF1:
            func_AAF1_b14(); break;
        case 0xB1C3:
            switch (g_current_bank) {
                case 0: func_B1C3_b0(); break;
                case 2: func_B1C3_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xF0C0:
            func_F0C0(); break;
        case 0xF0C8:
            func_F0C8(); break;
        case 0x80C4:
            func_80C4_b0(); break;
        case 0x8CC4:
            func_8CC4_b0(); break;
        case 0xED35:
            func_ED35(); break;
        case 0x8049:
            func_8049_b0(); break;
        case 0xECC4:
            func_ECC4(); break;
        case 0x857F:
            func_857F_b0(); break;
        case 0xF1C4:
            func_F1C4(); break;
        case 0xC052:
            func_C052(); break;
        case 0xC114:
            func_C114(); break;
        case 0xC054:
            func_C054(); break;
        case 0xB04E:
            func_B04E_b0(); break;
        case 0xCB2C:
            func_CB2C(); break;
        case 0xC981:
            func_C981(); break;
        case 0x8C70:
            func_8C70_b0(); break;
        case 0xF2C8:
            func_F2C8(); break;
        case 0xF0C1:
            func_F0C1(); break;
        case 0xCBA1:
            func_CBA1(); break;
        case 0xC10D:
            func_C10D(); break;
        case 0xCC70:
            func_CC70(); break;
        case 0xF0C2:
            func_F0C2(); break;
        case 0xC42C:
            func_C42C(); break;
        case 0xE602:
            func_E602(); break;
        case 0xC0A1:
            func_C0A1(); break;
        case 0xC34D:
            func_C34D(); break;
        case 0xB6AF:
            func_B6AF_b0(); break;
        case 0xB6BD:
            func_B6BD_b0(); break;
        case 0x8354:
            func_8354_b0(); break;
        case 0xB5F1:
            func_B5F1_b0(); break;
        case 0x992E:
            func_992E_b0(); break;
        case 0x9935:
            func_9935_b0(); break;
        case 0xB17D:
            func_B17D_b0(); break;
        case 0x932A:
            func_932A_b0(); break;
        case 0xCA4D:
            func_CA4D(); break;
        case 0xC862:
            func_C862(); break;
        case 0xCA0C:
            func_CA0C(); break;
        case 0x83AC:
            func_83AC_b0(); break;
        case 0xACC3:
            func_ACC3_b0(); break;
        case 0xB2C4:
            func_B2C4_b0(); break;
        case 0xC979:
            func_C979(); break;
        case 0xB1C5:
            func_B1C5_b0(); break;
        case 0xB0C5:
            func_B0C5_b0(); break;
        case 0x950C:
            func_950C_b0(); break;
        case 0xC1A1:
            func_C1A1(); break;
        case 0xC1A0:
            func_C1A0(); break;
        case 0xC594:
            func_C594(); break;
        case 0x8EAC:
            func_8EAC_b0(); break;
        case 0xC4A1:
            func_C4A1(); break;
        case 0x9C94:
            func_9C94_b0(); break;
        case 0x9738:
            func_9738_b0(); break;
        case 0x974A:
            func_974A_b0(); break;
        case 0xCDB4:
            func_CDB4(); break;
        case 0xA345:
            func_A345_b0(); break;
        case 0xA335:
            switch (g_current_bank) {
                case 0: func_A335_b0(); break;
                case 14: func_A335_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x878C:
            func_878C_b0(); break;
        case 0x87AD:
            switch (g_current_bank) {
                case 15: func_C7AD(); break;
                case 0: func_87AD_b0(); break;
                case 1: func_87AD_b1(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xC3A0:
            func_C3A0(); break;
        case 0xC014:
            func_C014(); break;
        case 0x9719:
            func_9719_b0(); break;
        case 0xA326:
            func_A326_b0(); break;
        case 0xDCB1:
            func_DCB1(); break;
        case 0x9430:
            func_9430_b0(); break;
        case 0x943A:
            func_943A_b0(); break;
        case 0x9444:
            func_9444_b0(); break;
        case 0x944C:
            func_944C_b0(); break;
        case 0x86EE:
            func_86EE_b0(); break;
        case 0x86F2:
            func_86F2_b0(); break;
        case 0x8FA2:
            func_8FA2_b0(); break;
        case 0xA15B:
            func_A15B_b0(); break;
        case 0xA13D:
            func_A13D_b0(); break;
        case 0xA143:
            func_A143_b0(); break;
        case 0x8AC0:
            func_8AC0_b0(); break;
        case 0x94D4:
            func_94D4_b0(); break;
        case 0x94F1:
            func_94F1_b0(); break;
        case 0x8D14:
            func_8D14_b0(); break;
        case 0x8D2E:
            func_8D2E_b0(); break;
        case 0x8C02:
            func_8C02_b0(); break;
        case 0x8BE5:
            func_8BE5_b0(); break;
        case 0x9EF3:
            func_9EF3_b0(); break;
        case 0x88B2:
            func_88B2_b0(); break;
        case 0x88EB:
            switch (g_current_bank) {
                case 15: func_C8EB(); break;
                case 0: func_88EB_b0(); break;
                case 2: func_88EB_b2(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA791:
            func_A791_b0(); break;
        case 0xA7AD:
            switch (g_current_bank) {
                case 0: func_A7AD_b0(); break;
                case 10: func_A7AD_b10(); break;
                case 14: func_A7AD_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA175:
            func_A175_b0(); break;
        case 0xA1BE:
            func_A1BE_b0(); break;
        case 0x9C87:
            func_9C87_b0(); break;
        case 0x9C77:
            func_9C77_b0(); break;
        case 0x961D:
            func_961D_b0(); break;
        case 0x92F8:
            func_92F8_b0(); break;
        case 0x930C:
            func_930C_b0(); break;
        case 0x9D7E:
            switch (g_current_bank) {
                case 0: func_9D7E_b0(); break;
                case 14: func_9D7E_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xB10E:
            func_B10E_b0(); break;
        case 0xA993:
            func_A993_b0(); break;
        case 0xB2AF:
            func_B2AF_b0(); break;
        case 0xB2B2:
            func_B2B2_b0(); break;
        case 0xA68C:
            func_A68C_b0(); break;
        case 0x97EB:
            func_97EB_b0(); break;
        case 0x97F4:
            func_97F4_b0(); break;
        case 0x9EC1:
            func_9EC1_b0(); break;
        case 0x9CBC:
            func_9CBC_b0(); break;
        case 0xB229:
            func_B229_b0(); break;
        case 0x93A8:
            func_93A8_b0(); break;
        case 0x90BA:
            func_90BA_b0(); break;
        case 0x82D6:
            func_82D6_b1(); break;
        case 0x82AD:
            func_82AD_b1(); break;
        case 0x82F9:
            func_82F9_b1(); break;
        case 0x849D:
            func_849D_b1(); break;
        case 0x9473:
            func_9473_b1(); break;
        case 0xD4D6:
            func_D4D6(); break;
        case 0xD5E1:
            func_D5E1(); break;
        case 0x9CCF:
            func_9CCF_b1(); break;
        case 0xBC71:
            func_BC71_b1(); break;
        case 0xB1CF:
            func_B1CF_b1(); break;
        case 0x8CB0:
            switch (g_current_bank) {
                case 1: func_8CB0_b1(); break;
                case 4: func_8CB0_b4(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x954C:
            func_954C_b1(); break;
        case 0x8A79:
            switch (g_current_bank) {
                case 15: func_CA79(); break;
                case 1: func_8A79_b1(); break;
                case 14: func_8A79_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x83A1:
            func_83A1_b1(); break;
        case 0x8FC5:
            func_8FC5_b1(); break;
        case 0xB296:
            func_B296_b1(); break;
        case 0x886C:
            func_886C_b1(); break;
        case 0x887A:
            func_887A_b1(); break;
        case 0x9DE6:
            func_9DE6_b1(); break;
        case 0x877F:
            func_877F_b1(); break;
        case 0x878D:
            func_878D_b1(); break;
        case 0x8CCF:
            func_8CCF_b1(); break;
        case 0xDDFA:
            func_DDFA(); break;
        case 0xA35C:
            func_A35C_b1(); break;
        case 0xB3C6:
            func_B3C6_b1(); break;
        case 0xA9F7:
            func_A9F7_b1(); break;
        case 0x903B:
            func_903B_b1(); break;
        case 0xAC0B:
            func_AC0B_b1(); break;
        case 0xB0D3:
            func_B0D3_b1(); break;
        case 0x974B:
            func_974B_b1(); break;
        case 0xBB50:
            func_BB50_b1(); break;
        case 0xC0D5:
            func_C0D5(); break;
        case 0xF0CC:
            func_F0CC(); break;
        case 0xD20C:
            func_D20C(); break;
        case 0x970C:
            func_970C_b1(); break;
        case 0x9EE7:
            func_9EE7_b1(); break;
        case 0xB71B:
            func_B71B_b1(); break;
        case 0xA533:
            func_A533_b1(); break;
        case 0x8D17:
            func_8D17_b1(); break;
        case 0x8D1B:
            func_8D1B_b1(); break;
        case 0x81CD:
            func_81CD_b1(); break;
        case 0x81A8:
            func_81A8_b1(); break;
        case 0xC104:
            func_C104(); break;
        case 0xFC30:
            func_FC30(); break;
        case 0xC400:
            func_C400(); break;
        case 0xA9C2:
            func_A9C2_b1(); break;
        case 0x9131:
            func_9131_b1(); break;
        case 0x8BA5:
            func_8BA5_b1(); break;
        case 0x821B:
            func_821B_b1(); break;
        case 0x8F27:
            func_8F27_b1(); break;
        case 0xA6F2:
            func_A6F2_b1(); break;
        case 0x9918:
            func_9918_b1(); break;
        case 0x858B:
            func_858B_b1(); break;
        case 0x97E2:
            func_97E2_b1(); break;
        case 0x97E6:
            func_97E6_b1(); break;
        case 0xB331:
            func_B331_b1(); break;
        case 0x90A0:
            func_90A0_b1(); break;
        case 0x90A3:
            func_90A3_b1(); break;
        case 0x9A69:
            func_9A69_b1(); break;
        case 0x9A7F:
            func_9A7F_b1(); break;
        case 0x88C2:
            func_88C2_b1(); break;
        case 0x8AE4:
            func_8AE4_b2(); break;
        case 0xC881:
            func_C881(); break;
        case 0x833A:
            func_833A_b2(); break;
        case 0xC564:
            func_C564(); break;
        case 0x80DB:
            func_80DB_b2(); break;
        case 0xA3AC:
            func_A3AC_b2(); break;
        case 0x85A7:
            switch (g_current_bank) {
                case 2: func_85A7_b2(); break;
                case 10: func_85A7_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xC558:
            func_C558(); break;
        case 0xA3C3:
            func_A3C3_b2(); break;
        case 0x95C6:
            func_95C6_b2(); break;
        case 0xC05D:
            func_C05D(); break;
        case 0x95C5:
            func_95C5_b2(); break;
        case 0x9C71:
            func_9C71_b2(); break;
        case 0xA925:
            func_A925_b2(); break;
        case 0xA93A:
            func_A93A_b2(); break;
        case 0xA181:
            func_A181_b2(); break;
        case 0x80C6:
            func_80C6_b2(); break;
        case 0x9730:
            func_9730_b2(); break;
        case 0x9724:
            func_9724_b2(); break;
        case 0x93D8:
            func_93D8_b2(); break;
        case 0x8C42:
            func_8C42_b2(); break;
        case 0x8D39:
            func_8D39_b2(); break;
        case 0x8D48:
            func_8D48_b2(); break;
        case 0x871C:
            func_871C_b2(); break;
        case 0x80F0:
            func_80F0_b2(); break;
        case 0x893B:
            func_893B_b2(); break;
        case 0x83A7:
            func_83A7_b2(); break;
        case 0x8B58:
            func_8B58_b2(); break;
        case 0x95C0:
            switch (g_current_bank) {
                case 2: func_95C0_b2(); break;
                case 14: func_95C0_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9411:
            func_9411_b2(); break;
        case 0x99A2:
            func_99A2_b2(); break;
        case 0x8ED0:
            func_8ED0_b2(); break;
        case 0x8F0C:
            func_8F0C_b2(); break;
        case 0xA567:
            func_A567_b2(); break;
        case 0xA0F7:
            func_A0F7_b2(); break;
        case 0x98ED:
            func_98ED_b2(); break;
        case 0x80CC:
            func_80CC_b2(); break;
        case 0x84F6:
            func_84F6_b2(); break;
        case 0x97DF:
            switch (g_current_bank) {
                case 2: func_97DF_b2(); break;
                case 8: func_97DF_b8(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x97E3:
            func_97E3_b2(); break;
        case 0xA4D6:
            switch (g_current_bank) {
                case 15: func_E4D6(); break;
                case 2: func_A4D6_b2(); break;
                case 14: func_A4D6_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x90F9:
            func_90F9_b2(); break;
        case 0x8BE6:
            func_8BE6_b2(); break;
        case 0xFF42:
            func_FF42(); break;
        case 0xA0B7:
            func_A0B7_b3(); break;
        case 0xA761:
            func_A761_b3(); break;
        case 0x8F49:
            func_8F49_b3(); break;
        case 0x9861:
            func_9861_b3(); break;
        case 0x9D79:
            func_9D79_b3(); break;
        case 0x9E17:
            func_9E17_b3(); break;
        case 0x8081:
            func_8081_b3(); break;
        case 0x9979:
            func_9979_b3(); break;
        case 0x8454:
            func_8454_b3(); break;
        case 0x8488:
            func_8488_b3(); break;
        case 0x93B5:
            func_93B5_b3(); break;
        case 0x895C:
            func_895C_b3(); break;
        case 0x92BB:
            func_92BB_b3(); break;
        case 0x8ABA:
            func_8ABA_b3(); break;
        case 0xE3EF:
            func_E3EF(); break;
        case 0xC040:
            func_C040(); break;
        case 0x8F17:
            func_8F17_b4(); break;
        case 0x9CC8:
            func_9CC8_b4(); break;
        case 0x9AE5:
            func_9AE5_b4(); break;
        case 0xB497:
            func_B497_b4(); break;
        case 0xB007:
            func_B007_b4(); break;
        case 0xF5FF:
            func_F5FF(); break;
        case 0x92CE:
            func_92CE_b4(); break;
        case 0xA35A:
            func_A35A_b4(); break;
        case 0x8B56:
            func_8B56_b4(); break;
        case 0xA0B8:
            func_A0B8_b4(); break;
        case 0xA67C:
            func_A67C_b4(); break;
        case 0xA252:
            func_A252_b4(); break;
        case 0x8698:
            func_8698_b4(); break;
        case 0x90EB:
            func_90EB_b4(); break;
        case 0xB66C:
            func_B66C_b4(); break;
        case 0xA080:
            func_A080_b4(); break;
        case 0xB361:
            func_B361_b4(); break;
        case 0xB8DA:
            func_B8DA_b4(); break;
        case 0xB8CC:
            func_B8CC_b4(); break;
        case 0x99D2:
            func_99D2_b4(); break;
        case 0x99B4:
            func_99B4_b4(); break;
        case 0x876B:
            func_876B_b4(); break;
        case 0xC701:
            func_C701(); break;
        case 0xFE4E:
            func_FE4E(); break;
        case 0x90E0:
            func_90E0_b4(); break;
        case 0x9700:
            func_9700_b4(); break;
        case 0x92DF:
            func_92DF_b4(); break;
        case 0xA6F7:
            func_A6F7_b4(); break;
        case 0xAECD:
            func_AECD_b4(); break;
        case 0xA402:
            func_A402_b4(); break;
        case 0x8C48:
            func_8C48_b4(); break;
        case 0x9389:
            func_9389_b4(); break;
        case 0x9396:
            func_9396_b4(); break;
        case 0x9398:
            func_9398_b4(); break;
        case 0xAE7B:
            func_AE7B_b4(); break;
        case 0xAEB7:
            func_AEB7_b4(); break;
        case 0xAE71:
            func_AE71_b4(); break;
        case 0xB6EE:
            func_B6EE_b4(); break;
        case 0xB42D:
            func_B42D_b4(); break;
        case 0x89D4:
            func_89D4_b4(); break;
        case 0xA2F4:
            func_A2F4_b4(); break;
        case 0xA44D:
            func_A44D_b4(); break;
        case 0x868B:
            func_868B_b4(); break;
        case 0xD4FA:
            func_D4FA(); break;
        case 0x9826:
            func_9826_b4(); break;
        case 0xE090:
            func_E090(); break;
        case 0x9810:
            func_9810_b4(); break;
        case 0xE6D4:
            func_E6D4(); break;
        case 0xA64C:
            func_A64C_b4(); break;
        case 0xA7DF:
            func_A7DF_b5(); break;
        case 0x94A7:
            func_94A7_b5(); break;
        case 0xB06A:
            func_B06A_b5(); break;
        case 0xAFCF:
            func_AFCF_b5(); break;
        case 0xE4FF:
            func_E4FF(); break;
        case 0x8CA6:
            func_8CA6_b5(); break;
        case 0x9039:
            func_9039_b5(); break;
        case 0x9015:
            func_9015_b5(); break;
        case 0x8EDC:
            func_8EDC_b5(); break;
        case 0x9F5C:
            func_9F5C_b5(); break;
        case 0x8F26:
            func_8F26_b5(); break;
        case 0x91FF:
            func_91FF_b5(); break;
        case 0xFF87:
            func_FF87(); break;
        case 0xF070:
            func_F070(); break;
        case 0xBEBC:
            func_BEBC_b6(); break;
        case 0xAFBD:
            func_AFBD_b6(); break;
        case 0x90CB:
            func_90CB_b6(); break;
        case 0x90CC:
            func_90CC_b6(); break;
        case 0x87F5:
            func_87F5_b6(); break;
        case 0xA040:
            func_A040_b6(); break;
        case 0xDEEA:
            func_DEEA(); break;
        case 0xDF7F:
            func_DF7F(); break;
        case 0xBCFE:
            func_BCFE_b6(); break;
        case 0x88D0:
            func_88D0_b6(); break;
        case 0xF4A4:
            func_F4A4(); break;
        case 0xD853:
            func_D853(); break;
        case 0x833F:
            func_833F_b6(); break;
        case 0x8E13:
            func_8E13_b6(); break;
        case 0x8E0D:
            func_8E0D_b6(); break;
        case 0x98CC:
            func_98CC_b6(); break;
        case 0x8CA2:
            func_8CA2_b6(); break;
        case 0x8C8B:
            func_8C8B_b6(); break;
        case 0x9C07:
            func_9C07_b6(); break;
        case 0x9BDA:
            func_9BDA_b6(); break;
        case 0x9BE1:
            func_9BE1_b6(); break;
        case 0xB0F0:
            func_B0F0_b6(); break;
        case 0xC020:
            func_C020(); break;
        case 0xAC02:
            func_AC02_b6(); break;
        case 0x8FEB:
            func_8FEB_b6(); break;
        case 0x8FD5:
            func_8FD5_b6(); break;
        case 0x8FEC:
            func_8FEC_b6(); break;
        case 0xA05B:
            func_A05B_b6(); break;
        case 0xBAB9:
            func_BAB9_b6(); break;
        case 0xA940:
            func_A940_b6(); break;
        case 0xF8F0:
            func_F8F0(); break;
        case 0x98A5:
            func_98A5_b6(); break;
        case 0x8505:
            func_8505_b6(); break;
        case 0xA83E:
            func_A83E_b6(); break;
        case 0x807A:
            func_807A_b6(); break;
        case 0xB036:
            func_B036_b6(); break;
        case 0xA43F:
            func_A43F_b6(); break;
        case 0xABD1:
            func_ABD1_b6(); break;
        case 0xA70B:
            func_A70B_b6(); break;
        case 0x9E6A:
            func_9E6A_b6(); break;
        case 0x8CE1:
            func_8CE1_b6(); break;
        case 0xADAF:
            func_ADAF_b6(); break;
        case 0xB6B5:
            func_B6B5_b6(); break;
        case 0x99C6:
            func_99C6_b6(); break;
        case 0x87D9:
            func_87D9_b6(); break;
        case 0x9481:
            func_9481_b6(); break;
        case 0x9435:
            func_9435_b6(); break;
        case 0xB423:
            func_B423_b7(); break;
        case 0x8BF9:
            func_8BF9_b7(); break;
        case 0x8BFB:
            func_8BFB_b7(); break;
        case 0xBD2F:
            func_BD2F_b7(); break;
        case 0x8392:
            func_8392_b7(); break;
        case 0xFF6B:
            func_FF6B(); break;
        case 0x887D:
            func_887D_b7(); break;
        case 0x86D4:
            func_86D4_b7(); break;
        case 0x9DAD:
            func_9DAD_b8(); break;
        case 0xFDFD:
            func_FDFD(); break;
        case 0x9C90:
            func_9C90_b8(); break;
        case 0x8F56:
            func_8F56_b8(); break;
        case 0x9F6C:
            func_9F6C_b8(); break;
        case 0xC080:
            func_C080(); break;
        case 0xCCD0:
            func_CCD0(); break;
        case 0xE070:
            func_E070(); break;
        case 0xF800:
            func_F800(); break;
        case 0xA020:
            switch (g_current_bank) {
                case 15: func_E020(); break;
                case 8: func_A020_b8(); break;
                case 10: func_A020_b10(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x9BCD:
            func_9BCD_b8(); break;
        case 0x844E:
            func_844E_b10(); break;
        case 0xAEC6:
            func_AEC6_b10(); break;
        case 0x92D0:
            func_92D0_b10(); break;
        case 0x8840:
            func_8840_b10(); break;
        case 0xA246:
            switch (g_current_bank) {
                case 10: func_A246_b10(); break;
                case 14: func_A246_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA248:
            func_A248_b10(); break;
        case 0xA024:
            func_A024_b10(); break;
        case 0x8F86:
            func_8F86_b10(); break;
        case 0x8F88:
            func_8F88_b10(); break;
        case 0x90B2:
            func_90B2_b10(); break;
        case 0xEF60:
            func_EF60(); break;
        case 0xA424:
            func_A424_b10(); break;
        case 0xAA1D:
            func_AA1D_b10(); break;
        case 0xAA47:
            func_AA47_b10(); break;
        case 0xA841:
            func_A841_b10(); break;
        case 0xAB0C:
            func_AB0C_b10(); break;
        case 0x8F52:
            func_8F52_b10(); break;
        case 0xA672:
            func_A672_b10(); break;
        case 0xA654:
            func_A654_b10(); break;
        case 0xA8ED:
            func_A8ED_b10(); break;
        case 0x9891:
            func_9891_b10(); break;
        case 0xA7EB:
            func_A7EB_b10(); break;
        case 0xAA9E:
            func_AA9E_b10(); break;
        case 0x858E:
            func_858E_b10(); break;
        case 0x8577:
            func_8577_b10(); break;
        case 0xE060:
            func_E060(); break;
        case 0x8810:
            func_8810_b10(); break;
        case 0x883B:
            func_883B_b11(); break;
        case 0x8843:
            func_8843_b11(); break;
        case 0x8235:
            func_8235_b11(); break;
        case 0x9F58:
            func_9F58_b12(); break;
        case 0x8671:
            func_8671_b12(); break;
        case 0x8381:
            func_8381_b12(); break;
        case 0xA97D:
            func_A97D_b12(); break;
        case 0x8221:
            func_8221_b12(); break;
        case 0x827D:
            func_827D_b12(); break;
        case 0x80C0:
            func_80C0_b12(); break;
        case 0x8DE5:
            func_8DE5_b12(); break;
        case 0x800E:
            func_800E_b12(); break;
        case 0x9004:
            func_9004_b12(); break;
        case 0x8508:
            func_8508_b12(); break;
        case 0xA944:
            func_A944_b12(); break;
        case 0x85BC:
            func_85BC_b12(); break;
        case 0x85A0:
            func_85A0_b12(); break;
        case 0x858D:
            func_858D_b12(); break;
        case 0x906D:
            func_906D_b12(); break;
        case 0x8D46:
            func_8D46_b12(); break;
        case 0xA714:
            func_A714_b12(); break;
        case 0xA46F:
            func_A46F_b12(); break;
        case 0xEEF3:
            func_EEF3(); break;
        case 0xE8ED:
            func_E8ED(); break;
        case 0x81AB:
            func_81AB_b12(); break;
        case 0x8427:
            func_8427_b14(); break;
        case 0x859C:
            func_859C_b14(); break;
        case 0xA6AF:
            func_A6AF_b14(); break;
        case 0x822D:
            func_822D_b14(); break;
        case 0x82D1:
            func_82D1_b14(); break;
        case 0x83D1:
            func_83D1_b14(); break;
        case 0x85C4:
            func_85C4_b14(); break;
        case 0x9DFD:
            func_9DFD_b14(); break;
        case 0x9D78:
            func_9D78_b14(); break;
        case 0xAD10:
            func_AD10_b14(); break;
        case 0x83E1:
            func_83E1_b14(); break;
        case 0xA8AC:
            func_A8AC_b14(); break;
        case 0x8410:
            func_8410_b14(); break;
        case 0xBD8F:
            func_BD8F_b14(); break;
        case 0xB758:
            func_B758_b14(); break;
        case 0xBCAF:
            func_BCAF_b14(); break;
        case 0xBB3F:
            func_BB3F_b14(); break;
        case 0xBB7E:
            func_BB7E_b14(); break;
        case 0xBCFB:
            func_BCFB_b14(); break;
        case 0xBB45:
            func_BB45_b14(); break;
        case 0xBBF0:
            func_BBF0_b14(); break;
        case 0x8419:
            func_8419_b14(); break;
        case 0x8564:
            func_8564_b14(); break;
        case 0xA523:
            func_A523_b14(); break;
        case 0xA529:
            func_A529_b14(); break;
        case 0xA51B:
            func_A51B_b14(); break;
        case 0xA510:
            func_A510_b14(); break;
        case 0xAD5F:
            func_AD5F_b14(); break;
        case 0xAD65:
            func_AD65_b14(); break;
        case 0xA8BF:
            func_A8BF_b14(); break;
        case 0xA8CE:
            func_A8CE_b14(); break;
        case 0x854C:
            func_854C_b14(); break;
        case 0x867B:
            func_867B_b14(); break;
        case 0xA4B4:
            func_A4B4_b14(); break;
        case 0xA0AD:
            func_A0AD_b14(); break;
        case 0x8507:
            func_8507_b14(); break;
        case 0xAEF8:
            func_AEF8_b14(); break;
        case 0xAF49:
            func_AF49_b14(); break;
        case 0xB0FC:
            func_B0FC_b14(); break;
        case 0x8AA2:
            func_8AA2_b14(); break;
        case 0x9593:
            func_9593_b14(); break;
        case 0xA885:
            func_A885_b14(); break;
        case 0x8398:
            func_8398_b14(); break;
        case 0x9DF7:
            func_9DF7_b14(); break;
        case 0x9E13:
            func_9E13_b14(); break;
        case 0xAC21:
            func_AC21_b14(); break;
        case 0xAC2D:
            func_AC2D_b14(); break;
        case 0xAC7E:
            func_AC7E_b14(); break;
        case 0xACDD:
            func_ACDD_b14(); break;
        case 0x8691:
            func_8691_b14(); break;
        case 0x98B2:
            func_98B2_b14(); break;
        case 0x9900:
            func_9900_b14(); break;
        case 0x8562:
            func_8562_b0(); break;
        case 0xF16C:
            func_F16C(); break;
        case 0xA960:
            switch (g_current_bank) {
                case 0: func_A960_b0(); break;
                case 1: func_A960_b1(); break;
                case 2: func_A960_b2(); break;
                case 3: func_A960_b3(); break;
                case 4: func_A960_b4(); break;
                case 5: func_A960_b5(); break;
                case 6: func_A960_b6(); break;
                case 7: func_A960_b7(); break;
                case 8: func_A960_b8(); break;
                case 9: func_A960_b9(); break;
                case 10: func_A960_b10(); break;
                case 11: func_A960_b11(); break;
                case 12: func_A960_b12(); break;
                case 13: func_A960_b13(); break;
                case 14: func_A960_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x92E5:
            func_92E5_b0(); break;
        case 0xA306:
            func_A306_b0(); break;
        case 0x8764:
            func_8764_b0(); break;
        case 0x8774:
            func_8774_b0(); break;
        case 0x8A97:
            func_8A97_b0(); break;
        case 0x8A9F:
            func_8A9F_b0(); break;
        case 0x9C6A:
            func_9C6A_b0(); break;
        case 0xA96B:
            func_A96B_b0(); break;
        case 0x9E98:
            func_9E98_b0(); break;
        case 0x93A2:
            func_93A2_b0(); break;
        case 0x8A75:
            func_8A75_b1(); break;
        case 0x8378:
            func_8378_b1(); break;
        case 0xB284:
            func_B284_b1(); break;
        case 0x8754:
            func_8754_b1(); break;
        case 0x971C:
            func_971C_b1(); break;
        case 0x969D:
            func_969D_b1(); break;
        case 0x96A1:
            func_96A1_b1(); break;
        case 0x9E97:
            func_9E97_b1(); break;
        case 0x9ECC:
            func_9ECC_b1(); break;
        case 0x8CCC:
            func_8CCC_b1(); break;
        case 0xA962:
            func_A962_b1(); break;
        case 0x9126:
            func_9126_b1(); break;
        case 0x90C6:
            func_90C6_b1(); break;
        case 0x90F4:
            func_90F4_b1(); break;
        case 0x8EB0:
            func_8EB0_b1(); break;
        case 0x8F11:
            func_8F11_b1(); break;
        case 0x856B:
            func_856B_b1(); break;
        case 0x9A0D:
            func_9A0D_b1(); break;
        case 0x8333:
            func_8333_b2(); break;
        case 0x856F:
            func_856F_b2(); break;
        case 0x93EF:
            func_93EF_b2(); break;
        case 0x9407:
            func_9407_b2(); break;
        case 0x8ECB:
            switch (g_current_bank) {
                case 2: func_8ECB_b2(); break;
                case 5: func_8ECB_b5(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0xA0D2:
            func_A0D2_b2(); break;
        case 0x97DA:
            func_97DA_b2(); break;
        case 0x90F2:
            func_90F2_b2(); break;
        case 0x8B47:
            func_8B47_b4(); break;
        case 0xB8B5:
            func_B8B5_b4(); break;
        case 0x8C7E:
            func_8C7E_b4(); break;
        case 0x96E2:
            func_96E2_b4(); break;
        case 0x8667:
            func_8667_b4(); break;
        case 0x8689:
            func_8689_b4(); break;
        case 0xA780:
            func_A780_b5(); break;
        case 0xB044:
            func_B044_b5(); break;
        case 0xA035:
            func_A035_b6(); break;
        case 0xBCE0:
            func_BCE0_b6(); break;
        case 0xBCD4:
            func_BCD4_b6(); break;
        case 0x82B5:
            func_82B5_b6(); break;
        case 0x82CC:
            func_82CC_b6(); break;
        case 0xBA3D:
            func_BA3D_b6(); break;
        case 0x98A2:
            func_98A2_b6(); break;
        case 0xA809:
            func_A809_b6(); break;
        case 0x9E2A:
            func_9E2A_b6(); break;
        case 0x8178:
            func_8178_b12(); break;
        case 0x85AD:
            func_85AD_b14(); break;
        case 0x82A2:
            func_82A2_b14(); break;
        case 0x8575:
            func_8575_b14(); break;
        case 0xBD3C:
            func_BD3C_b14(); break;
        case 0xBD4A:
            func_BD4A_b14(); break;
        case 0xA53C:
            func_A53C_b14(); break;
        case 0x9E12:
            func_9E12_b14(); break;
        case 0xA951:
            func_A951_b0(); break;
        case 0xA955:
            func_A955_b2(); break;
        case 0x92B9:
            func_92B9_b0(); break;
        case 0x832B:
            func_832B_b1(); break;
        case 0x9E25:
            func_9E25_b1(); break;
        case 0x9E6D:
            switch (g_current_bank) {
                case 1: func_9E6D_b1(); break;
                case 14: func_9E6D_b14(); break;
                default: nes_log_dispatch_miss(addr); break;
            }
            break;
        case 0x8E59:
            func_8E59_b1(); break;
        case 0x853E:
            func_853E_b1(); break;
        case 0x8317:
            func_8317_b2(); break;
        case 0x93E6:
            func_93E6_b2(); break;
        case 0x98EA:
            func_98EA_b2(); break;
        case 0xB83E:
            func_B83E_b4(); break;
        case 0x9684:
            func_9684_b4(); break;
        case 0xBC8A:
            func_BC8A_b6(); break;
        case 0xBC9C:
            func_BC9C_b6(); break;
        case 0xBA2A:
            func_BA2A_b6(); break;
        case 0x8146:
            func_8146_b12(); break;
        case 0xBD45:
            func_BD45_b14(); break;
        case 0x9E0B:
            func_9E0B_b1(); break;
        case 0x9E1B:
            func_9E1B_b1(); break;
        case 0x9E53:
            func_9E53_b1(); break;
        case 0x82F6:
            func_82F6_b2(); break;
        case 0xBC92:
            func_BC92_b6(); break;
        case 0x82DD:
            func_82DD_b2(); break;
        case 0x8C98:
            func_8C98_b14(); break;
        case 0xA313:
            func_A313_b14(); break;
        case 0x8D6E:
            func_8D6E_b14(); break;
        case 0x9EE4:
            func_9EE4_b14(); break;
        case 0x8E44:
            func_8E44_b14(); break;
        case 0x8E57:
            func_8E57_b14(); break;
        case 0x8EC2:
            func_8EC2_b14(); break;
        case 0x8F18:
            func_8F18_b14(); break;
        case 0x8FD9:
            func_8FD9_b14(); break;
        case 0xA120:
            func_A120_b14(); break;
        case 0x9033:
            func_9033_b14(); break;
        case 0x9044:
            func_9044_b14(); break;
        case 0x90DF:
            func_90DF_b14(); break;
        case 0x910F:
            func_910F_b14(); break;
        case 0x918E:
            func_918E_b14(); break;
        case 0x921F:
            func_921F_b14(); break;
        case 0x9ADC:
            func_9ADC_b14(); break;
        case 0x822E:
            func_822E_b14(); break;
        case 0x9261:
            func_9261_b14(); break;
        case 0x92B0:
            func_92B0_b14(); break;
        case 0x93AC:
            func_93AC_b14(); break;
        case 0x9442:
            func_9442_b14(); break;
        case 0x9453:
            func_9453_b14(); break;
        case 0x9513:
            func_9513_b14(); break;
        case 0x951C:
            func_951C_b14(); break;
        case 0x9535:
            func_9535_b14(); break;
        case 0x95AE:
            func_95AE_b14(); break;
        case 0x961B:
            func_961B_b14(); break;
        case 0x96EA:
            func_96EA_b14(); break;
        case 0x9704:
            func_9704_b14(); break;
        case 0x975E:
            func_975E_b14(); break;
        case 0x9770:
            func_9770_b14(); break;
        case 0x979B:
            func_979B_b14(); break;
        case 0x9853:
            func_9853_b14(); break;
        case 0x98B3:
            func_98B3_b14(); break;
        case 0x9C51:
            func_9C51_b14(); break;
        case 0x9CD0:
            func_9CD0_b14(); break;
        case 0x9D94:
            func_9D94_b14(); break;
        case 0x9FC4:
            func_9FC4_b14(); break;
        case 0xA06E:
            func_A06E_b14(); break;
        case 0xA28D:
            func_A28D_b14(); break;
        case 0xA290:
            func_A290_b14(); break;
        case 0xA2A0:
            func_A2A0_b14(); break;
        case 0xA2BE:
            func_A2BE_b14(); break;
        case 0xA2FE:
            func_A2FE_b14(); break;
        case 0xA304:
            func_A304_b14(); break;
        case 0xA30A:
            func_A30A_b14(); break;
        case 0xA34B:
            func_A34B_b14(); break;
        case 0xA0E8:
            func_A0E8_b14(); break;
        case 0xA1C2:
            func_A1C2_b14(); break;
        case 0xA1F5:
            func_A1F5_b14(); break;
        case 0xA5D2:
            func_A5D2_b14(); break;
        case 0x8279:
            func_8279_b14(); break;
        case 0x89AE:
            func_89AE_b14(); break;
        case 0x8957:
            func_8957_b14(); break;
        case 0x89EF:
            func_89EF_b14(); break;
        case 0x88FB:
            func_88FB_b14(); break;
        case 0xA6FF:
            func_A6FF_b14(); break;
        case 0xA72C:
            func_A72C_b14(); break;
        case 0xA772:
            func_A772_b14(); break;
        case 0xA7E5:
            func_A7E5_b14(); break;
        case 0xA86E:
            func_A86E_b14(); break;
        case 0xA74C:
            func_A74C_b14(); break;
        case 0xA84F:
            func_A84F_b14(); break;
        case 0xA6E8:
            func_A6E8_b14(); break;
        case 0xA8FC:
            func_A8FC_b14(); break;
        case 0xA98B:
            func_A98B_b14(); break;
        case 0x9A32:
            func_9A32_b14(); break;
        case 0xABCC:
            func_ABCC_b14(); break;
        case 0xA9DE:
            func_A9DE_b14(); break;
        case 0x9B83:
            func_9B83_b14(); break;
        case 0x9CF2:
            func_9CF2_b14(); break;
        case 0x9DA9:
            func_9DA9_b14(); break;
        case 0x9F03:
            func_9F03_b14(); break;
        case 0x9FE3:
            func_9FE3_b14(); break;
        case 0xAA86:
            func_AA86_b14(); break;
        case 0xA8D7:
            func_A8D7_b14(); break;
        case 0xA978:
            func_A978_b14(); break;
        case 0x8DA3:
            func_8DA3_b14(); break;
        case 0x8ECF:
            func_8ECF_b14(); break;
        case 0x8F2E:
            func_8F2E_b14(); break;
        case 0x8FE7:
            func_8FE7_b14(); break;
        case 0x9060:
            func_9060_b14(); break;
        case 0xA0CB:
            func_A0CB_b14(); break;
        case 0xA11D:
            func_A11D_b14(); break;
        case 0xA154:
            func_A154_b14(); break;
        case 0xAB26:
            func_AB26_b14(); break;
        case 0x92E0:
            func_92E0_b14(); break;
        case 0x93E5:
            func_93E5_b14(); break;
        case 0x9538:
            func_9538_b14(); break;
        case 0x9632:
            func_9632_b14(); break;
        case 0x971D:
            func_971D_b14(); break;
        case 0x97AE:
            func_97AE_b14(); break;
        case 0x9865:
            func_9865_b14(); break;
        case 0xA25F:
            func_A25F_b14(); break;
        case 0xA354:
            func_A354_b14(); break;
        case 0xA384:
            func_A384_b14(); break;
        case 0xA3BF:
            func_A3BF_b14(); break;
        case 0xA3EF:
            func_A3EF_b14(); break;
        case 0xA413:
            func_A413_b14(); break;
        case 0xA437:
            func_A437_b14(); break;
        case 0xA45B:
            func_A45B_b14(); break;
        case 0xA48A:
            func_A48A_b14(); break;
        case 0xA49D:
            func_A49D_b14(); break;
        case 0xA4B0:
            func_A4B0_b14(); break;
        case 0xA4C3:
            func_A4C3_b14(); break;
        case 0xA4FC:
            func_A4FC_b14(); break;
        case 0xA4E9:
            func_A4E9_b14(); break;
        case 0xA31E:
            func_A31E_b14(); break;
        case 0xA558:
            func_A558_b14(); break;
        case 0xA56F:
            func_A56F_b14(); break;
        case 0xA586:
            func_A586_b14(); break;
        case 0xA47F:
            func_A47F_b14(); break;
        case 0xAB67:
            func_AB67_b14(); break;
        case 0x8E77:
            func_8E77_b14(); break;
        case 0x9129:
            func_9129_b14(); break;
        case 0x91B3:
            func_91B3_b14(); break;
        case 0xBBE7:
            func_BBE7_b14(); break;
        case 0xBC66:
            func_BC66_b14(); break;
        case 0xBC74:
            func_BC74_b14(); break;
        case 0xBC82:
            func_BC82_b14(); break;
        case 0xBC90:
            func_BC90_b14(); break;
        case 0xBAEC:
            func_BAEC_b14(); break;
        case 0xBC9F:
            func_BC9F_b14(); break;
        case 0xBB6B:
            func_BB6B_b14(); break;
        case 0xBB91:
            func_BB91_b14(); break;
        case 0xBBD9:
            func_BBD9_b14(); break;
        case 0xBC5B:
            func_BC5B_b14(); break;
        case 0x8B72:
            func_8B72_b14(); break;
        case 0xAC75:
            func_AC75_b14(); break;
        case 0xAC9F:
            func_AC9F_b14(); break;
        case 0x8408:
            func_8408_b5(); break;
        case 0x84A5:
            func_84A5_b5(); break;
        case 0x8DD8:
            func_8DD8_b5(); break;
        case 0x8DEB:
            func_8DEB_b5(); break;
        case 0x8C9C:
            func_8C9C_b5(); break;
        case 0x8D36:
            func_8D36_b5(); break;
        case 0x8D5F:
            func_8D5F_b5(); break;
        case 0x8C69:
            func_8C69_b5(); break;
        case 0x8C73:
            func_8C73_b5(); break;
        case 0x8BB3:
            func_8BB3_b5(); break;
        case 0x8BC5:
            func_8BC5_b5(); break;
        case 0x869E:
            func_869E_b5(); break;
        case 0x86A8:
            func_86A8_b5(); break;
        case 0x89A8:
            func_89A8_b5(); break;
        case 0x89B2:
            func_89B2_b5(); break;
        case 0x8A47:
            func_8A47_b5(); break;
        case 0x880A:
            func_880A_b5(); break;
        case 0x881F:
            func_881F_b5(); break;
        case 0x8A9D:
            func_8A9D_b5(); break;
        case 0x8AA7:
            func_8AA7_b5(); break;
        case 0x8877:
            func_8877_b5(); break;
        case 0x8B65:
            func_8B65_b5(); break;
        case 0x8B6F:
            func_8B6F_b5(); break;
        case 0x88D2:
            func_88D2_b5(); break;
        case 0x8ADA:
            func_8ADA_b5(); break;
        case 0x8A05:
            func_8A05_b5(); break;
        case 0x8743:
            func_8743_b5(); break;
        case 0x86D3:
            func_86D3_b5(); break;
        case 0x86E0:
            func_86E0_b5(); break;
        case 0x8771:
            func_8771_b5(); break;
        case 0x877B:
            func_877B_b5(); break;
        case 0x8973:
            func_8973_b5(); break;
        case 0x8982:
            func_8982_b5(); break;
        case 0x8C1E:
            func_8C1E_b5(); break;
        case 0x87C2:
            func_87C2_b5(); break;
        case 0x82C5:
            func_82C5_b12(); break;
        case 0x82EF:
            func_82EF_b12(); break;
        case 0x82D9:
            func_82D9_b12(); break;
        case 0x8726:
            func_8726_b12(); break;
        case 0x835B:
            func_835B_b12(); break;
        case 0x8391:
            func_8391_b12(); break;
        case 0x839F:
            func_839F_b12(); break;
        case 0x83D8:
            func_83D8_b12(); break;
        case 0x85D1:
            func_85D1_b12(); break;
        case 0x85F6:
            func_85F6_b12(); break;
        case 0x85E6:
            func_85E6_b12(); break;
        case 0x8630:
            func_8630_b12(); break;
        case 0x8657:
            func_8657_b12(); break;
        case 0x8660:
            func_8660_b12(); break;
        case 0x8718:
            func_8718_b12(); break;
        case 0x85AF:
            func_85AF_b12(); break;
        case 0x82AE:
            func_82AE_b12(); break;
        case 0xD654:
            func_D654(); break;
        case 0xD673:
            func_D673(); break;
        case 0xD699:
            func_D699(); break;
        case 0xC39B:
            func_C39B(); break;
        case 0xC3A7:
            func_C3A7(); break;
        case 0xC3B6:
            func_C3B6(); break;
        case 0xC3C9:
            func_C3C9(); break;
        case 0xC3D6:
            func_C3D6(); break;
        case 0xC3FB:
            func_C3FB(); break;
        case 0xC403:
            func_C403(); break;
        case 0xA8B8:
            func_A8B8_b14(); break;
        case 0x927D:
            func_927D_b14(); break;
        case 0x961A:
            func_961A_b14(); break;
        case 0xA2EB:
            func_A2EB_b14(); break;
        case 0xA5CB:
            func_A5CB_b14(); break;
        case 0x89AD:
            func_89AD_b14(); break;
        case 0x8998:
            func_8998_b14(); break;
        case 0xC764:
            func_C764(); break;
        case 0xA771:
            func_A771_b14(); break;
        case 0x9917:
            func_9917_b14(); break;
        case 0x9A2F:
            func_9A2F_b14(); break;
        case 0x9A2C:
            func_9A2C_b14(); break;
        case 0x9B45:
            func_9B45_b14(); break;
        case 0x9C0E:
            func_9C0E_b14(); break;
        case 0x9C43:
            func_9C43_b14(); break;
        case 0x9F86:
            func_9F86_b14(); break;
        case 0x8329:
            func_8329_b14(); break;
        case 0xEFE6:
            func_EFE6(); break;
        case 0xCA6E:
            func_CA6E(); break;
        case 0x831B:
            func_831B_b14(); break;
        case 0xA91E:
            func_A91E_b14(); break;
        case 0x8F9A:
            func_8F9A_b14(); break;
        case 0x9360:
            func_9360_b14(); break;
        case 0xA259:
            func_A259_b14(); break;
        case 0xA256:
            func_A256_b14(); break;
        case 0xA250:
            func_A250_b14(); break;
        case 0xA3B4:
            func_A3B4_b14(); break;
        case 0xA093:
            func_A093_b14(); break;
        case 0xC752:
            func_C752(); break;
        case 0x9991:
            func_9991_b14(); break;
        case 0x994A:
            func_994A_b14(); break;
        case 0x99D1:
            func_99D1_b14(); break;
        case 0x9947:
            func_9947_b14(); break;
        case 0x9A3C:
            func_9A3C_b14(); break;
        case 0x8C0F:
            func_8C0F_b14(); break;
        case 0x828E:
            func_828E_b5(); break;
        case 0xC2E9:
            func_C2E9(); break;
        default:
            nes_log_dispatch_miss(addr);
            break;
    }
}
