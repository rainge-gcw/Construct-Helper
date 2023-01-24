//
// Created by oceanstar on 2021/8/13.
//

#ifndef OCEANSTAR_HTTP_ACL_BASE64_H
#define OCEANSTAR_HTTP_ACL_BASE64_H

namespace oceanstar{
    /*
     * BASE64 编码函数
     * @param in {const char*} 源数据
     * @param len {int} in 源数据的长度
     * @return unsigned char * 编码结果，需要free释放
     */
    unsigned char *acl_base64_encode(const char *in, int len);


    /*
     * BASE64 解码函数
     * @param in {const char*} 编码后的数据
     * @param len {int} in 数据长度
     * @return unsigned char * NULL: 解码失败; !=NULL: 解码成功需要free释放
     */
    unsigned char *acl_base64_decode(const char *in, int len);
}
#endif //OCEANSTAR_HTTP_ACL_BASE64_H

