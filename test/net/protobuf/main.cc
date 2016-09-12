#include "system.pb.h"
#include "Clock.hpp"
#include <sstream>
#include <iostream>

#define MAX_SIZE        (1000 * 1000)

void effectioncy(void)
{
        MsgHeart mh;
        mh.set_guid(123);
        std::string tmpStr = "a";
        for (int i=0; i<MAX_SIZE/100; ++i)
                tmpStr += "a";
        mh.set_name(tmpStr);

        printf("name_size = %lu\n", mh.name().size());

        std::string tmp;
        {
                CTimeCost t("SerializeToString");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        mh.SerializeToString(&tmp);
        }
        printf("tmp.size() = %lu\n", tmp.size());

        char buff[10240] = {0};
        {
                CTimeCost t("SerializeToArray ByteSize");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        mh.SerializeToArray(buff, mh.ByteSize());
        }

        {
                CTimeCost t("SerializeToArray GetCachedSize");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        mh.SerializeToArray(buff, mh.GetCachedSize());
        }

        {
                CTimeCost t("ByteSize");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        mh.ByteSize();
        }
        printf("ByteSize = %d\n", mh.ByteSize());

        {
                CTimeCost t("GetCachedSize");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                        mh.GetCachedSize();
        }
        printf("GetCachedSize = %d\n", mh.GetCachedSize());

        // mh.SerializePartialToArray(buff, mh.ByteSize());
        // mh.InternalSerializeWithCachedSizesToArray(false, NULL);

        /* IsInitialized() 方法是检测 required 字段有没有被设置
        MsgHeart tmpMH;
        printf("111 tmpMH.IsInitialized() = %s\n", tmpMH.IsInitialized() ? "true" : "false");
        tmpMH.set_guid(1);
        printf("222 tmpMH.IsInitialized() = %s\n", tmpMH.IsInitialized() ? "true" : "false");
        tmpMH.Clear();
        printf("333 tmpMH.IsInitialized() = %s\n", tmpMH.IsInitialized() ? "true" : "false");
        */

        /*
        std::ostringstream stream;
        {
                CTimeCost t("SerializeToOstream");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                {
                        stream.clear();
                        mh.SerializeToOstream(&stream);
                }
        }
        printf("stream size = %lu\n", stream.str().size());
        */
}

using namespace google::protobuf;

void reflection()
{
        typedef MsgHeart T;

        const std::string type_name = T::descriptor()->full_name();
        printf("type_name = %s\n", type_name.c_str());

        const Descriptor* descriptor = DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
        std::cout << "FindMessageTypeByName() = " << descriptor << std::endl;
        std::cout << "T::descriptor()  = " << T::descriptor() << std::endl << std::endl;

        const Message* prototype = MessageFactory::generated_factory()->GetPrototype(descriptor);
        std::cout << "GetPrototype()        = " << prototype << std::endl;
        std::cout << "T::default_instance() = " << &T::default_instance() << std::endl;
        std::cout << std::endl;

        T* new_obj = dynamic_cast<T*>(prototype->New());
        assert(new_obj != NULL);
        assert(new_obj != prototype);
        assert(typeid(*new_obj) == typeid(T::default_instance()));
        std::cout << "prototype->New() = " << new_obj << std::endl;
        std::cout << std::endl;

        delete new_obj;
}

void effectioncy_mutable()
{
        MsgHeart mh;
        {
                CTimeCost t("mutable");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                {
                        mh.Clear();
                        mh.mutable_item();
                }
        }

        {
                CTimeCost t("new");
                for (int32_t i=0; i<MAX_SIZE; ++i)
                {
                        mh.Clear();
                        // mh.item = new MsgHeartItem();
                }
        }
}

void TestSize()
{
        MsgTestBool mtb;

        mtb.set_test_1(true);
        mtb.set_test_2(true);
        mtb.set_test_3(true);
        mtb.set_test_4(true);
        mtb.set_test_5(true);
        mtb.set_test_6(true);
        mtb.set_test_7(true);
        mtb.set_test_8(true);
        mtb.set_test_9(true);
        mtb.set_test_10(true);
        mtb.set_test_11(true);
        mtb.set_test_12(true);
        mtb.set_test_13(true);
        mtb.set_test_14(true);
        mtb.set_test_15(true);
        mtb.set_test_16(true);
        mtb.set_test_17(true);
        mtb.set_test_18(true);
        mtb.set_test_19(true);
        mtb.set_test_20(true);
        mtb.set_test_21(true);
        mtb.set_test_22(true);
        mtb.set_test_23(true);
        mtb.set_test_24(true);
        mtb.set_test_25(true);
        mtb.set_test_26(true);
        mtb.set_test_27(true);
        mtb.set_test_28(true);
        mtb.set_test_29(true);
        mtb.set_test_30(true);
        mtb.set_test_31(true);
        mtb.set_test_32(true);


        std::string tmp;
        mtb.SerializeToString(&tmp);
        printf("SerializeToString size = %lu\n", tmp.size());

        printf("mtb.ByteSize() = %d\n", mtb.ByteSize());
        printf("mtb.GetCachedSize() = %d\n", mtb.GetCachedSize());
}

template <typename T>
void testCombine_SetFiled(T obj)
{
        obj->set_id(123);
        obj->set_name("lsw");
        obj->set_email_1("nvngliu@gmail.com");
        obj->set_email_2("nvngliu@gmail.com");
        obj->set_email_3("nvngliu@gmail.com");
        obj->set_email_4("nvngliu@gmail.com");
        obj->set_email_5("nvngliu@gmail.com");
        obj->set_email_6("nvngliu@gmail.com");
        obj->set_email_7("nvngliu@gmail.com");
        obj->set_email_8("nvngliu@gmail.com");
        obj->set_email_9("nvngliu@gmail.com");
        obj->set_email_10("nvngliu@gmail.com");
        obj->set_email_11("nvngliu@gmail.com");
        obj->set_email_12("nvngliu@gmail.com");
        obj->set_email_13("nvngliu@gmail.com");
        obj->set_email_14("nvngliu@gmail.com");
        obj->set_email_15("nvngliu@gmail.com");
        obj->set_email_16("nvngliu@gmail.com");
        obj->set_email_17("nvngliu@gmail.com");
        obj->set_email_18("nvngliu@gmail.com");
        obj->set_email_19("nvngliu@gmail.com");
        obj->set_email_20("nvngliu@gmail.com");
        obj->set_email_21("nvngliu@gmail.com");
}

void testCombine()
{
        char buff[10240] = {0};
        TestCombine msg;
        {
                testCombine_SetFiled(msg.mutable_obj_0());
                testCombine_SetFiled(msg.mutable_obj_1());
                testCombine_SetFiled(msg.mutable_obj_2());
                testCombine_SetFiled(msg.mutable_obj_3());
                testCombine_SetFiled(msg.mutable_obj_4());
                testCombine_SetFiled(msg.mutable_obj_5());
                testCombine_SetFiled(msg.mutable_obj_6());
                testCombine_SetFiled(msg.mutable_obj_7());
                testCombine_SetFiled(msg.mutable_obj_8());
                testCombine_SetFiled(msg.mutable_obj_9());
                testCombine_SetFiled(msg.mutable_obj_10());
                testCombine_SetFiled(msg.mutable_obj_11());
                testCombine_SetFiled(msg.mutable_obj_12());
                testCombine_SetFiled(msg.mutable_obj_13());
                testCombine_SetFiled(msg.mutable_obj_14());
                testCombine_SetFiled(msg.mutable_obj_15());
                testCombine_SetFiled(msg.mutable_obj_16());
                testCombine_SetFiled(msg.mutable_obj_17());
                testCombine_SetFiled(msg.mutable_obj_18());
                testCombine_SetFiled(msg.mutable_obj_19());
                testCombine_SetFiled(msg.mutable_obj_20());

                printf("msg size = %d\n", msg.ByteSize());
                printf("msg size = %d\n", msg.GetCachedSize());

                CTimeCost t("combine");
                for (int32_t i=0; i<MAX_SIZE/100; ++i)
                        msg.SerializeToArray(buff, msg.ByteSize());
        }

        const int32_t byteSize = msg.ByteSize();
        {
                CTimeCost t("combine par");
                for (int32_t i=0; i<MAX_SIZE/100; ++i)
                {
                        msg.ParseFromArray(buff, byteSize);
                        // msg.Clear();
                }
        }

        {
                TestCombine_0 msg_0;
                testCombine_SetFiled(&msg_0);
                TestCombine_1 msg_1;
                testCombine_SetFiled(&msg_1);
                TestCombine_2 msg_2;
                testCombine_SetFiled(&msg_2);
                TestCombine_3 msg_3;
                testCombine_SetFiled(&msg_3);
                TestCombine_4 msg_4;
                testCombine_SetFiled(&msg_4);
                TestCombine_5 msg_5;
                testCombine_SetFiled(&msg_5);
                TestCombine_6 msg_6;
                testCombine_SetFiled(&msg_6);
                TestCombine_7 msg_7;
                testCombine_SetFiled(&msg_7);
                TestCombine_8 msg_8;
                testCombine_SetFiled(&msg_8);
                TestCombine_9 msg_9;
                testCombine_SetFiled(&msg_9);
                TestCombine_10 msg_10;
                testCombine_SetFiled(&msg_10);
                TestCombine_11 msg_11;
                testCombine_SetFiled(&msg_11);
                TestCombine_12 msg_12;
                testCombine_SetFiled(&msg_12);
                TestCombine_13 msg_13;
                testCombine_SetFiled(&msg_13);
                TestCombine_14 msg_14;
                testCombine_SetFiled(&msg_14);
                TestCombine_15 msg_15;
                testCombine_SetFiled(&msg_15);
                TestCombine_16 msg_16;
                testCombine_SetFiled(&msg_16);
                TestCombine_17 msg_17;
                testCombine_SetFiled(&msg_17);
                TestCombine_18 msg_18;
                testCombine_SetFiled(&msg_18);
                TestCombine_19 msg_19;
                testCombine_SetFiled(&msg_19);
                TestCombine_20 msg_20;
                testCombine_SetFiled(&msg_20);

                msg_0.ByteSize();
                msg_1.ByteSize();
                msg_2.ByteSize();
                msg_3.ByteSize();
                msg_4.ByteSize();
                msg_5.ByteSize();
                msg_6.ByteSize();
                msg_7.ByteSize();
                msg_8.ByteSize();
                msg_9.ByteSize();
                msg_10.ByteSize();
                msg_11.ByteSize();
                msg_12.ByteSize();
                msg_13.ByteSize();
                msg_14.ByteSize();
                msg_15.ByteSize();
                msg_16.ByteSize();
                msg_17.ByteSize();
                msg_18.ByteSize();
                msg_19.ByteSize();
                msg_20.ByteSize();

                {
                CTimeCost t("sp");
                for (int32_t i=0; i<MAX_SIZE/100; ++i)
                {
#if 0
                        msg_0.SerializeToArray(buff, msg_0.GetCachedSize());
                        msg_1.SerializeToArray(buff, msg_1.GetCachedSize());
                        msg_2.SerializeToArray(buff, msg_2.GetCachedSize());
                        msg_3.SerializeToArray(buff, msg_3.GetCachedSize());
                        msg_4.SerializeToArray(buff, msg_4.GetCachedSize());
                        msg_5.SerializeToArray(buff, msg_5.GetCachedSize());
                        msg_6.SerializeToArray(buff, msg_6.GetCachedSize());
                        msg_7.SerializeToArray(buff, msg_7.GetCachedSize());
                        msg_8.SerializeToArray(buff, msg_8.GetCachedSize());
                        msg_9.SerializeToArray(buff, msg_9.GetCachedSize());
                        msg_10.SerializeToArray(buff, msg_10.GetCachedSize());
                        msg_11.SerializeToArray(buff, msg_11.GetCachedSize());
                        msg_12.SerializeToArray(buff, msg_12.GetCachedSize());
                        msg_13.SerializeToArray(buff, msg_13.GetCachedSize());
                        msg_14.SerializeToArray(buff, msg_14.GetCachedSize());
                        msg_15.SerializeToArray(buff, msg_15.GetCachedSize());
                        msg_16.SerializeToArray(buff, msg_16.GetCachedSize());
                        msg_17.SerializeToArray(buff, msg_17.GetCachedSize());
                        msg_18.SerializeToArray(buff, msg_18.GetCachedSize());
                        msg_19.SerializeToArray(buff, msg_19.GetCachedSize());
                        msg_20.SerializeToArray(buff, msg_20.GetCachedSize());
#else
                        msg_0.SerializeToArray(buff, msg_0.ByteSize());
                        msg_1.SerializeToArray(buff, msg_1.ByteSize());
                        msg_2.SerializeToArray(buff, msg_2.ByteSize());
                        msg_3.SerializeToArray(buff, msg_3.ByteSize());
                        msg_4.SerializeToArray(buff, msg_4.ByteSize());
                        msg_5.SerializeToArray(buff, msg_5.ByteSize());
                        msg_6.SerializeToArray(buff, msg_6.ByteSize());
                        msg_7.SerializeToArray(buff, msg_7.ByteSize());
                        msg_8.SerializeToArray(buff, msg_8.ByteSize());
                        msg_9.SerializeToArray(buff, msg_9.ByteSize());
                        msg_10.SerializeToArray(buff, msg_10.ByteSize());
                        msg_11.SerializeToArray(buff, msg_11.ByteSize());
                        msg_12.SerializeToArray(buff, msg_12.ByteSize());
                        msg_13.SerializeToArray(buff, msg_13.ByteSize());
                        msg_14.SerializeToArray(buff, msg_14.ByteSize());
                        msg_15.SerializeToArray(buff, msg_15.ByteSize());
                        msg_16.SerializeToArray(buff, msg_16.ByteSize());
                        msg_17.SerializeToArray(buff, msg_17.ByteSize());
                        msg_18.SerializeToArray(buff, msg_18.ByteSize());
                        msg_19.SerializeToArray(buff, msg_19.ByteSize());
                        msg_20.SerializeToArray(buff, msg_20.ByteSize());
#endif
                }
                }

                const int32_t byteSize = msg_0.ByteSize();
                {
                        CTimeCost t("sp par");
                        for (int32_t i=0; i<MAX_SIZE/100; ++i)
                        {
                                msg_0.ParseFromArray(buff, byteSize);
                                msg_1.ParseFromArray(buff, byteSize);
                                msg_2.ParseFromArray(buff, byteSize);
                                msg_3.ParseFromArray(buff, byteSize);
                                msg_4.ParseFromArray(buff, byteSize);
                                msg_5.ParseFromArray(buff, byteSize);
                                msg_6.ParseFromArray(buff, byteSize);
                                msg_7.ParseFromArray(buff, byteSize);
                                msg_8.ParseFromArray(buff, byteSize);
                                msg_9.ParseFromArray(buff, byteSize);
                                msg_10.ParseFromArray(buff, byteSize);
                                msg_11.ParseFromArray(buff, byteSize);
                                msg_12.ParseFromArray(buff, byteSize);
                                msg_13.ParseFromArray(buff, byteSize);
                                msg_14.ParseFromArray(buff, byteSize);
                                msg_15.ParseFromArray(buff, byteSize);
                                msg_16.ParseFromArray(buff, byteSize);
                                msg_17.ParseFromArray(buff, byteSize);
                                msg_18.ParseFromArray(buff, byteSize);
                                msg_19.ParseFromArray(buff, byteSize);
                                msg_20.ParseFromArray(buff, byteSize);

                                /*
                                msg_0.Clear();
                                msg_1.Clear();
                                msg_2.Clear();
                                msg_3.Clear();
                                msg_4.Clear();
                                msg_5.Clear();
                                msg_6.Clear();
                                msg_7.Clear();
                                msg_8.Clear();
                                msg_9.Clear();
                                msg_10.Clear();
                                msg_11.Clear();
                                msg_12.Clear();
                                msg_13.Clear();
                                msg_14.Clear();
                                msg_15.Clear();
                                msg_16.Clear();
                                msg_17.Clear();
                                msg_18.Clear();
                                msg_19.Clear();
                                msg_20.Clear();
                                */
                        }
                }
        }
}

int main(void)
{
        // reflection();
        effectioncy();
        // effectioncy_mutable();
        // TestSize();
        // testCombine();

        return 0;
}
