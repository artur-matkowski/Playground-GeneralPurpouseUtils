#ifndef H_SerializerBase
#define H_SerializerBase
#include <vector>
#include <cstdint>

namespace bfu2
{
	class SerializerBase
	{
	public:

		virtual void Serialize(std::vector<char>& v_buff, const SerializerBase* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<SerializerBase>* data) = 0;

		virtual void Serialize(std::vector<char>& v_buff, const float* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<float>* data) = 0;

		virtual void Serialize(std::vector<char>& v_buff, const double* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<double>* data) = 0;

		virtual void Serialize(std::vector<char>& v_buff, const bool* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<bool>* data) = 0;

		virtual void Serialize(std::vector<char>& v_buff, const char* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<char>* data) = 0;


		virtual void Serialize(std::vector<char>& v_buff, const uint8_t* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<uint8_t>* data) = 0;

		virtual void Serialize(std::vector<char>& v_buff, const uint16_t* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<uint16_t>* data) = 0;

		virtual void Serialize(std::vector<char>& v_buff, const uint32_t* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<uint32_t>* data) = 0;

		virtual void Serialize(std::vector<char>& v_buff, const uint64_t* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<uint64_t>* data) = 0;


		virtual void Serialize(std::vector<char>& v_buff, const int8_t* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<int8_t>* data) = 0;

		virtual void Serialize(std::vector<char>& v_buff, const int16_t* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<int16_t>* data) = 0;

		virtual void Serialize(std::vector<char>& v_buff, const int32_t* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<int32_t>* data) = 0;

		virtual void Serialize(std::vector<char>& v_buff, const int64_t* data) = 0;
		virtual void Serialize(std::vector<char>& v_buff, const std::vector<int64_t>* data) = 0;
	};
}

#endif