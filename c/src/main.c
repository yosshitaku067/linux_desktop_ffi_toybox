#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <asn_internal.h>
#include <asn_application.h>
#include <xer_encoder.h>

#include <Rocket.h>

// static char buf[4096];
// static int buf_offset;

// static int
// buf_writer(const void *buffer, size_t size, void *app_key)
// {
//     (void)app_key;
//     assert(buf_offset + size < sizeof(buf));
//     memcpy(buf + buf_offset, buffer, size);
//     buf_offset += size;
//     return 0;
// }

#ifdef __cplusplus
extern "C"
{
#endif

    int add(int num1, int num2)
    {
        return num1 + num2;
    }

    // // 16進数文字列 -> XML文字列
    // char *hex_to_xml(char *input_hex)
    // {
    //     size_t input_len = strlen(input_hex) / 2;
    //     uint8_t *input_buf = (u_int8_t *)malloc(input_len);
    //     for (size_t i = 0; i < input_len; i++)
    //     {
    //         sscanf(input_hex + i * 2, "%2hhx", &input_buf[i]);
    //     }

    //     Rocket_t *rocket = NULL;
    //     asn_dec_rval_t rval = uper_decode(NULL, &asn_DEF_Rocket, (void **)&rocket, input_buf, input_len, 0, 0);
    //     if (rval.code != RC_OK)
    //     {
    //         fprintf(stderr, "Error decoding input buffer: %s\n", strerror(errno));
    //     }

    //     asn_enc_rval_t er = xer_encode(&asn_DEF_Rocket, rocket, XER_F_BASIC, buf_writer, NULL);
    //     if (er.encoded == -1)
    //     { // エンコードに失敗した場合
    //         fprintf(stderr, "Failed to encode ASN.1 data to XML: %s\n", strerror(errno));
    //         free(buf);
    //         return NULL;
    //     }
    //     buf[buf_offset] = 0;

    //     return buf;
    // }

    // // XML文字列 -> 16進数文字列
    // void xml_to_hex()
    // {
    // }

    // void hex_check()
    // {
    // }

    // void xml_check()
    // {
    // }

    // void gen_dummy_rocket_hex()
    // {
    // }

    // int convert(char *input_hex)
    // {

    //     size_t input_len = strlen(input_hex) / 2;
    //     uint8_t *input_buf = (u_int8_t *)malloc(input_len);
    //     for (size_t i = 0; i < input_len; i++)
    //     {
    //         sscanf(input_hex + i * 2, "%2hhx", &input_buf[i]);
    //     }

    //     Rocket_t *rocket = NULL;
    //     asn_dec_rval_t rval = uper_decode(NULL, &asn_DEF_Rocket, (void **)&rocket, input_buf, input_len, 0, 0);
    //     if (rval.code != RC_OK)
    //     {
    //         fprintf(stderr, "Error decoding input buffer: %s\n", strerror(errno));
    //     }

    //     // asn_fprint(stdout, &asn_DEF_Rocket, rocket);

    //     // xer_fprint(stdout, &asn_DEF_Rocket, rocket);

    //     asn_enc_rval_t er = xer_encode(&asn_DEF_Rocket, rocket, XER_F_BASIC, buf_writer, NULL);
    //     if (er.encoded == -1)
    //     { // エンコードに失敗した場合
    //         fprintf(stderr, "Failed to encode ASN.1 data to XML: %s\n", strerror(errno));
    //         free(buf);
    //         return NULL;
    //     }
    //     buf[buf_offset] = 0;

    //     printf("%s\n", buf);

    //     // // asn_fprint(stdout, &asn_DEF_Rocket, &xml);

    //     // uint8_t *uper_buf = NULL;
    //     // size_t uper_len = uper_encode_to_new_buffer(&asn_DEF_Rocket, NULL, rocket, &uper_buf);

    //     // if (uper_len == -1)
    //     // {
    //     //     printf("UPER encode failed: %s\n", asn_DEF_Rocket.xml_tag);
    //     // }

    //     // for (int i = 0; i < uper_len; i++)
    //     // {
    //     //     printf("%02x", uper_buf[i]);
    //     // }

    //     // printf("\n");

    //     // ASN_STRUCT_FREE(asn_DEF_Rocket, rocket);
    //     // free(uper_buf);
    //     // free(input_buf);

    //     // return uper_len;

    //     return 0;
    // }

    void gen()
    {
        Rocket_t rocket;
        rocket.range = 10000;
        UTF8String_t name;
        name.buf = (uint8_t *)"Falcon 9";
        name.size = strlen((const char *)name.buf);
        rocket.name = name;
        rocket.fuel = Rocket__fuel_liquid;

        Rocket_t *rocket_ptr = &rocket;
        rocket_ptr->speed = (struct speed *)calloc(1, sizeof(struct speed *));
        rocket_ptr->speed->present = Rocket__speed_PR_mph;
        rocket_ptr->speed->choice.mph = 12000;

        UTF8String_t message;
        message.buf = (uint8_t *)"Hello World";
        message.size = strlen((const char *)message.buf);
        rocket_ptr->message = &message;

        UTF8String_t payload1;
        payload1.buf = (uint8_t *)"Payload 1";
        payload1.size = strlen((const char *)payload1.buf);
        UTF8String_t payload2;
        payload2.buf = (uint8_t *)"Payload 2";
        payload2.size = strlen((const char *)payload2.buf);

        asn_sequence_add(&rocket_ptr->payload.list, &payload1);
        asn_sequence_add(&rocket_ptr->payload.list, &payload2);

        uint8_t *uper_buf = NULL;
        size_t uper_len = uper_encode_to_new_buffer(&asn_DEF_Rocket, NULL, &rocket, &uper_buf);
        // char result[uper_len];

        if ((int)uper_len == -1)
        {
            printf("UPER encode failed: %s\n", asn_DEF_Rocket.xml_tag);
        }

        for (int i = 0; i < (int)uper_len; i++)
        {
            printf("%02x", uper_buf[i]);
            // sprintf(result + 2*i, "%02x", uper_buf[i]);
        }

        printf("\n");
        // result[2*uper_len] = '\0';

        // return result;
    }

#ifdef __cplusplus
}
#endif

int main(int argc, char **argv)
{
    // char dummy_hex = gen();
    // printf("%s\n", &dummy_hex);
    gen();

    return 0;
}