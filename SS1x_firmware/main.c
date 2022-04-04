#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include "hal.h"
#include "simpleserial.h"
#include "api.h"
#include "katrng.h"
#include "inner.h"
#include "fft.h"
#include "nist.h"
//#include "fpr.h"

#define TEMPALLOC
#define NONCELEN   40

fpr hm, f;

unsigned char *sm;
unsigned long long *smlen;
const unsigned char *m;
unsigned long long mlen = 33;
const unsigned char *sk;

uint64_t transform(uint8_t *in) {
    uint64_t result = 0;
    for (int i = 0; i < 8; i++) { //8
        result |= in[i];
        if (i != 7) //7
            result <<= 8;
    }
    return result;
}

uint64_t transform1(uint8_t *in) {
    uint64_t result = 0;
    for (int i = 0; i < 2; i++) { //8
        result |= in[i];
        if (i != 1) //7
            result <<= 8;
    }
    return result;
}

uint8_t set_f(uint8_t *text_in_buf, uint8_t len) {
    f = transform(text_in_buf);
    return 0;
}

// hm 값을 설정한다.
uint8_t sign(uint8_t *text_in_buf, uint8_t len) {

//    m="D81C4D8D734FCBFBEADE3D3F8A039FAA2A2C9957E835AD55B22E75BF57BB556AC8";
//    sk="59044102F3CFBE1BE03C144102F7EF75FBEF83043F7CFC20C20BEEC007DE3F041FBF0BFF401041030C40040FAE7E103F7E100085FC013D1410C80C2F000810461C2F480BEE8017D17F07F1411BA24013C1BDF83DC407D17E07C13917F0F9044045FC40BD0FF07D07EF0003DFC1F3CFFD1FC03FEFC0B8FC6E7B0BBDBD0FE0BE17D14307EFFE0FBFC6F81FBFF43EC1F87041D42083EC3DC2F4407BF84EC4140FC403F037F3FEC013E0FEE02180082F83FBE07BFFE043F40EC6FFB1BF200007FFBFFA0FFF6FFBCE83EBFEBEFC0FFDF3F103FC6F3FF0500A18718308007D03F200E4213BF04FFD17D000F0017A17F180E04FFF07DEC2244048148E8704503EE06F86080243F81FFF03BF4003F07EF3DE02FBFFC00420C1F40FBDF0707E043FF5FFD0000430400C4F49F4207C142F80EC3E010BFF7C13F07FF85F7F17E07C17FF33FC4EC303FFBCFFEEC41830FF0831BDF45F05F06FC503B0C0F84E4013E100E7E1441450C2FBEEBC0C0FBEFC60BCFFEF3CFBDF4303EF800BF2BE0BF001F01F43F41FFE08517B001141E00144F7EF8007CEBDFFFF4213A0B9F8A0FE04103C17E0820BB1C30C30C00FFFFC00007D18017CFF90C3101E7E103040FC4FBE04213E07AF80FFEFC80FBFBD0810BCFB8FBC087FB8FFF1010C2E81002F3EF3BF01F07E41FBC07F2C0FB8F43F401C5D81FFCEBE07C07E0BF17EEBEE830C514003FF7EF3E08403D1FFFFE105F840C20BDF0607FFFEF46E7EFFF08000400DE830000F3F82EF9D82E84EFFF3CEC4E81E01002103102EFC080F3B0801041BAE42F7F040F83EC31010031BC0410FAFF9F0004010133A089FFEF7BE8317A0020FEF010052BA04107E100F821C2F41F44F4EF7B000F02E41F82F380830FE08A1F707FF82EC7F42E81004041103E8307B13D0FDFF8F830F9FC5FFCD7E040F410FFFB9F423750860C11C5FFA144EC0080F02DC0F420820450790020BCF80EFFFBCEC4FBFF4200AFC00C02060C004303EF81FFA104107E4117AF01F81202FC1E44143FFE206EB3E881BB13F13920403FF7A000144102E7FFC2143E7FF4AF3F13F07E181DC317E240F4500303F2DDDCF1E1513E3EF15E8DC1309E50AEE03EFDC17081706FD03E6ECE4F30EBD1909051906E90CE806EB0B19E719EFFBF10D0DF1DC0CF6F1F4F8FEFBE9F9550E2107FCDCCBDFE9F4F7EE1AF8142115F910002AF2F5FF141ADA220AECFE040CEF0B29EB201930F2D3E401E5DEEFF4DDEA17F1FE141217F81C36050109F8F61F02DD19F90310C7F40208E9052C3942F8FFF2CCF9FDF83CFA12DC091C0D02F00411F5281E40D7F92DBA11D73D04C10BFD13E617110AF3ED05F6CFE705E0F70E1FF80533FC120C002CE81FF52638190FE3FED6F0FBBB23E6F408EF32220B13DD27F007E5FA00D72614F0E302210707EC111E070E2A032DF91DE3FCE800F1F9F2F7FE170101180412CBD1E90019F2011522DAEAED13F8E5F425DCEF24E01CE614E7DCEC01F2F4F914F4010107ED26E2E9DF0BF5F007EA07FAFBC6D7E607FAFCFD270DFD0D17FC4EF0EE00071AECDE09F8F215E113F80209CCF308D7E6251ECE0EDFED0CC9F4050B2714F61BF703F0EBF104010DEBFBF21AFC1BF01823FEDEFAF7F807E3F3020AEB01FE19EEE8E90D00E5FAED1EFDF628E5F0E6F0FC13F4FB05FB0B09EA0A0E08EE13293212E90CE4FEF223F4FF030BEBED1B402ED2F6171102BC0CF9E9F335ED0C01FAF0FEFAE41DF0050A162C11171CD90BEE211218EDFAFA0F03F4171412F319D60B01FAEE1F2823F0D6EF12D6DFEAFBFC170DECDA06E7CED500031E";
//    crypto_sign(sm, &smlen, m, mlen, sk);
//    fpr fpct_a_re='c18832928d3bca60', fpct_a_im='c187c9bd5d45bba6'; \
//    fpr fpct_b_re='c03828bb90a8aabc', fpct_b_im='403864ec11b96315'; \
//    fpr fpct_d_re, fpct_d_im; \
//    trigger_high();
//    fpct_d_re = fpr_sub(\
//        fpr_mul(fpct_a_re, fpct_b_re), \
//        fpr_mul(fpct_a_im, fpct_b_im)); \
//    fpct_d_im = fpr_add(\
//        fpr_mul(fpct_a_re, fpct_b_im), \
//        fpr_mul(fpct_a_im, fpct_b_re)); \
//    trigger_low();
    hm = transform(text_in_buf);
    uint64_t xu, yu, w, zu, zv;
    uint32_t x0, x1, y0, y1, z0, z1, z2;
    int ex, ey, e, s, d;
//    fpr x = 'c18832928d3bca60';
//    fpr y = 'c03828bb90a8aabc';
    xu = (hm & (((uint64_t) 1 << 52) - 1)) | ((uint64_t) 1 << 52); //1.xx 값의 곱셈이르모 앞에 1을 붙힘 (하위 25비트, 상위 28비트)
    yu = (f & (((uint64_t) 1 << 52) - 1)) | ((uint64_t) 1 << 52);

    trigger_high();
    x0 = (uint32_t) xu & 0x01FFFFFF;
//    x1 = (uint32_t) (xu >> 25);
    y0 = (uint32_t) yu & 0x01FFFFFF;
//    y1 = (uint32_t) (yu >> 25);
    w = (uint64_t) x0 * (uint64_t) y0;
    trigger_low();
//    z0 = (uint32_t) w & 0x01FFFFFF;
//    z1 = (uint32_t) (w >> 25);
//    w = (uint64_t) x0 * (uint64_t) y1;
//    z1 += (uint32_t) w & 0x01FFFFFF;
//    z2 = (uint32_t) (w >> 25);
//    w = (uint64_t) x1 * (uint64_t) y0;
//    z1 += (uint32_t) w & 0x01FFFFFF;
//    z2 += (uint32_t) (w >> 25);
//    zu = (uint64_t) x1 * (uint64_t) y1;
//    z2 += (z1 >> 25);
//    z1 &= 0x01FFFFFF;
//    zu += z2;
//    zu |= ((z0 | z1) + 0x01FFFFFF) >> 25;
//    zv = (zu >> 1) | (zu & 1);
//    w = zu >> 55;
//    zu ^= (zu ^ zv) & -w;
//    d = (int) transform1(text_in_buf);
//
//    ex = d; //(int) ((hm >> 52) & 0x7FF);
//    ey = 1075; // (int) ((f >> 52) & 0x7FF);
//    trigger_high();
//    e = ex + ey - 2100; //+ (int) w;
////    s =  (int)((hm ^ f) >> 63);
////    d = ((ex + 0x7FF) & (ey + 0x7FF)) >> 11;
////    zu &= -(uint64_t)d;
//    asm("nop");
//    asm("nop");
//    asm("nop");
//    asm("nop");
//    asm("nop");
//    trigger_low();
//    uint8_t buf[2];
//    buf[0] = (e >> 8) & 0x07;
//    buf[1] = e & 0xFF;
//    simpleserial_put('r', 2, buf);

//	trigger_high();
//	Zf(poly_mul_fft)(hm, b01, logn);
//	trigger_low();
    //Zf(poly_mulconst)(hm, ni, logn);
    return 0;
}

uint8_t check_f(uint8_t *text_in_buf, uint8_t len) {
    uint8_t buf[8];
    for (int i = 0; i < 8; i++)
        buf[i] = (f >> (8 * (7 - i))) & 0xff;
    simpleserial_put('r', 8, buf);
    return 0;
}

uint8_t check_hm(uint8_t *text_in_buf, uint8_t len) {
    uint8_t buf[8];
    for (int i = 0; i < 8; i++)
        buf[i] = (hm >> (8 * (7 - i))) & 0xff;
    simpleserial_put('r', 8, buf);
    return 0;
}

//// hm 값을 설정한다.
//uint8_t set_hm(uint8_t *text_in_buf, uint8_t len) {
//    // trigger_high();
//
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            hm[i] += (((fpr) text_in_buf[i * 8 + j]) << (56 - 8 * j));
//        }
//    }
//    // trigger_low();
//
//    return 0;
//}

int main(void) {


    platform_init();
    init_uart();
    trigger_setup();
    /* Uncomment this to get a HELLO message for debug */
    /*
    putch('h');
    putch('e');
    putch('l');
    putch('l');
    putch('o');
    putch('\n');
    */

    simpleserial_init();  // 'v': check_version, 'y': ss_num_commands, 'w': ss_get_commands

    simpleserial_addcmd('f', 8, set_f);
    simpleserial_addcmd('s', 8, sign);
    simpleserial_addcmd('c', 0, check_f);
    simpleserial_addcmd('h', 0, check_hm);
    while (1)
        simpleserial_get();
}
