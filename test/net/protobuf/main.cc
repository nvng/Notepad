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

        MsgHeart tmpMH;
        printf("111 tmpMH.IsInitialized() = %s\n", tmpMH.IsInitialized() ? "true" : "false");
        tmpMH.set_guid(1);
        printf("222 tmpMH.IsInitialized() = %s\n", tmpMH.IsInitialized() ? "true" : "false");
        tmpMH.Clear();
        printf("333 tmpMH.IsInitialized() = %s\n", tmpMH.IsInitialized() ? "true" : "false");

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

        8
        8
        8
        8
        8
        8
        8
        8
        8
        8

        mtb.set_test_1
                (true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);
        mtb.set_test_(true);


        std::string tmp;
        mtb.SerializeToString(&tmp);
        printf("SerializeToString size = %lu\n", tmp.size());

        printf("mtb.ByteSize() = %d\n", mtb.ByteSize());
        printf("mtb.GetCachedSize() = %d\n", mtb.GetCachedSize());
}

int main(void)
{
        // reflection();
        // effectioncy();
        // effectioncy_mutable();
        TestSize();

        return 0;
}
