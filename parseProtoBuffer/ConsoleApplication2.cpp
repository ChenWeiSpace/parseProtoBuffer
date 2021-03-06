// ConsoleApplication2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "test.pb.h"
#include <google/protobuf/message_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/descriptor.pb.h>
#include <google/protobuf/dynamic_message.h>
#include <sstream>
#include <fstream>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google\protobuf\stubs\io_win32.h>
#include <google/protobuf/text_format.h>
#include "sizeValue.pb.h"
#include "ft.pb.h"

void doT()
{
	std::fstream fielStrem("C:\\Users\\chenwei\\Desktop\\temp\\zip\\f.txt", std::ios_base::in | std::ios_base::binary);
	fielStrem.is_open();
	google::protobuf::io::IstreamInputStream input(&fielStrem);


	std::fstream fielStremout("C:\\Users\\chenwei\\Desktop\\temp\\zip\\f.dec", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	fielStremout.is_open();
	google::protobuf::io::OstreamOutputStream strea(&fielStremout);

	google::protobuf::DescriptorPool pool;
	google::protobuf::FileDescriptorProto file;
	file.set_name("empty_message.proto");
	file.add_message_type()->set_name("EmptyMessage");
	pool.BuildFile(file);
	std::string codec_type_ = "EmptyMessage";
	const google::protobuf::Descriptor* type = pool.FindMessageTypeByName(codec_type_);
	if (type == NULL) {
		std::cerr << "Type not defined: " << codec_type_ << std::endl;

	}
	google::protobuf::DynamicMessageFactory dynamic_factory(&pool);
	std::unique_ptr<google::protobuf::Message> message(dynamic_factory.GetPrototype(type)->New());

	message->ParsePartialFromZeroCopyStream(&input);

	google::protobuf::io::FileOutputStream out(STDOUT_FILENO);
	if (!google::protobuf::TextFormat::Print(*message, &strea)) {
		std::cerr << "output: I/O error." << std::endl;

	}

 	
// 	PrintUnknownFields(reflection->GetUnknownFields(message), generator);

}
void UnSerialize( std::string insFile, std::string outFile)
{
	std::fstream fielStrem(insFile, std::ios_base::in | std::ios_base::binary);
	if (!fielStrem.is_open())
	{
		return;
	}
	google::protobuf::io::IstreamInputStream input(&fielStrem);


	std::fstream fielStremout(outFile, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	fielStremout.is_open();
	google::protobuf::io::OstreamOutputStream strea(&fielStremout);

	google::protobuf::DescriptorPool pool;
	google::protobuf::FileDescriptorProto file;
	file.set_name("empty_message.proto");
	file.add_message_type()->set_name("EmptyMessage");
	pool.BuildFile(file);
	std::string codec_type_ = "EmptyMessage";
	const google::protobuf::Descriptor* type = pool.FindMessageTypeByName(codec_type_);
	if (type == NULL) {
		std::cerr << "Type not defined: " << codec_type_ << std::endl;

	}
	google::protobuf::DynamicMessageFactory dynamic_factory(&pool);
	std::unique_ptr<google::protobuf::Message> message(dynamic_factory.GetPrototype(type)->New());

	message->ParsePartialFromZeroCopyStream(&input);

	google::protobuf::io::FileOutputStream out(STDOUT_FILENO);
	if (!google::protobuf::TextFormat::Print(*message, &strea)) {
		std::cerr << "output: I/O error." << std::endl;

	}
}
void doT(std::string & str)
{
	google::protobuf::DescriptorPool pool;
	google::protobuf::FileDescriptorProto file;
	file.set_name("empty_message.proto");
	file.add_message_type()->set_name("EmptyMessage");
	pool.BuildFile(file);
	std::string codec_type_ = "EmptyMessage";
	const google::protobuf::Descriptor* type = pool.FindMessageTypeByName(codec_type_);
	if (type == NULL) {
		std::cerr << "Type not defined: " << codec_type_ << std::endl;

	}
	google::protobuf::DynamicMessageFactory dynamic_factory(&pool);
	std::unique_ptr<google::protobuf::Message> message(dynamic_factory.GetPrototype(type)->New());

	message->ParsePartialFromString(str);
	google::protobuf::io::FileOutputStream out(STDOUT_FILENO);
	if (!google::protobuf::TextFormat::Print(*message, &out)) {
		std::cerr << "output: I/O error." << std::endl;
		
	}
}
void doSize()
{
// 	UnSerialize("C:\\Users\\chenwei\\Desktop\\temp\\zip\\f.txt", "C:\\Users\\chenwei\\Desktop\\temp\\zip\\f.dec");
// 	return;

	//google::protobuf::io::FileInputStream in(STDIN_FILENO);
	//google::protobuf::io::FileOutputStream out(STDOUT_FILENO);

	std::fstream fielStremout("sizeValuef.sec", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	if (fielStremout.is_open())
	{
		tutorial::sizeValue * d = new tutorial::sizeValue;
		d->set_sz(-15);
		d->set_st(453);
		d->add_str(1.2);
		d->add_str(9.5);
		d->add_szr(100);
		d->add_szr(9999);

		d->ByteSizeLong();
// 		d->add_ssd(15); d->ByteSizeLong();
// 		d->add_ssd(150); d->ByteSizeLong();
// 		d->add_ssd(88989); d->ByteSizeLong();
		d->SerializePartialToOstream(&fielStremout);
		fielStremout.close();

		std::fstream fielStrem("sizeValuef.sec", std::ios_base::in | std::ios_base::binary);
		if (fielStrem.is_open())
		{
			tutorial::sizeValue * d1 = new tutorial::sizeValue;
			d1->ParseFromIstream(&fielStrem);
		}



		UnSerialize("sizeValuef.sec", "sizeValuef.dec");
	}
}
void doS()
{
	tutorial::arrayAndMsg * ar = new tutorial::arrayAndMsg;
	ar->add_sz(10);
	ar->add_sz(500);
	ar->add_sz(6666);
	ar->add_ar()->set_ky(12);
	std::fstream fielStremout("sizeValuef.sec", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	google::protobuf::io::OstreamOutputStream strea(&fielStremout);
	if (fielStremout.is_open())
	{
		ar->SerializePartialToOstream(&fielStremout);
		fielStremout.close();
	}
}
void doS(int pos,int l,std::string inFile,std::string outFile)
{
	std::fstream fielStrem(inFile, std::ios_base::in | std::ios_base::binary);

	std::fstream fielStremout(outFile, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	if (fielStrem.is_open() && fielStremout.is_open())
	{
		fielStrem.tellg();
		fielStrem.seekg(pos, std::ios::ios_base::beg);
		std::string str;
		str.resize(l);
		fielStrem.read((char*)str.data(),l);
		if (fielStrem.good())
		{
			fielStremout.write(str.data(), str.size());;
		}
		fielStrem.close();
		fielStremout.close();
	}
}

template<typename T>
void toStream(T file, std::ostream & stream,std::string pix)
{
	stream.precision(10);
	int s = file->size();
	stream << "cout::" << std::to_string(file->size())<<";  ";

	for (int i = 0; i < s; ++i)
	{
		stream << file->Get(i)<< ",";
	}
	stream << "\n";
}

template<>
void toStream(std::string* file, std::ostream & stream, std::string pix)
{
	int s = file->size();
	stream << "<string>-cout::" << std::to_string(file->size()) << ";  ";
	if (file->size() < 50 )
	{
		stream << *file;
	}
	//stream << *file;
	stream << "\n";
}

void savaFile(Console::top * t, std::string filePath)
{
	std::fstream fielStremout(filePath, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
	if (fielStremout.is_open())
	{
		fielStremout << "IsInitialized::" << t->IsInitialized()<<"\n";

		std::string pix;
		fielStremout << "f1:";
		toStream(t->mutable_f1(), fielStremout, pix);


		int s = t->f2_size();
		for (int i = 0; i < s; ++i)
		{
			fielStremout << "f2:" << "\n";
			pix.push_back('\t');

			auto f2 = t->mutable_f2(i);
			fielStremout << pix<< "IsInitialized::" << f2->IsInitialized() << "\n";

			fielStremout << pix << "f1:";
			toStream(f2->mutable_f1(), fielStremout, pix);

			fielStremout << pix << "f3:";
			toStream(f2->mutable_f3(), fielStremout, pix);

			fielStremout << pix << "f6:" << "\n";

			pix.push_back('\t');
			{
				auto f6 = f2->mutable_f6();
				fielStremout << pix << "f1:";
				toStream(f6->mutable_f1(), fielStremout, pix);

				fielStremout << pix << "f2:" << f6->f2() << "\n";
				fielStremout << pix << "f3:" << f6->f3() << "\n";
			}

			pix.pop_back();


			fielStremout << pix << "f7:";
			toStream(f2->mutable_f7(), fielStremout, pix);

			fielStremout << pix << "f8:";
			toStream(f2->mutable_f8(), fielStremout, pix);

			fielStremout << pix << "f11:";
			toStream(f2->mutable_f11(), fielStremout, pix);

			fielStremout << pix << "f12:" << f2->f12() << "\n";

			fielStremout << pix << "f13:";
			toStream(f2->mutable_f13(), fielStremout, pix);

			pix.pop_back();
		}
		

		

		fielStremout << "f3:";
		toStream(t->mutable_f3(), fielStremout, pix);

		fielStremout << "f5:";
		toStream(t->mutable_f5(), fielStremout, pix);

		pix.push_back('\t');
		fielStremout << "f7:" << "\n";
		{
			auto f2 = t->mutable_f7();
			fielStremout << pix << "f1:";
			toStream(f2->mutable_f1(), fielStremout, pix);

			fielStremout << pix << "f2:";
			toStream(f2->mutable_f2(), fielStremout, pix);

			fielStremout << pix << "f3:";
			toStream(f2->mutable_f3(), fielStremout, pix);

			fielStremout << pix << "f11:";
			toStream(f2->mutable_f11(), fielStremout, pix);

		}
		pix.pop_back();

		fielStremout << "f8:";
		toStream(t->mutable_f8(), fielStremout, pix);

	}
	fielStremout << "UnkonwField:"<<"\n";

	if (t->GetReflection()->GetUnknownFields(*t).field_count())
	{
		google::protobuf::io::OstreamOutputStream strea(&fielStremout);
		google::protobuf::TextFormat::PrintUnknownFields(t->GetReflection()->GetUnknownFields(*t), &strea);
	}
}

void guess(std::string str)
{
	Console::top * t = new Console::top;
	//std::string str = "C:\\Users\\chenwei\\Desktop\\temp\\zip\\f (3)";
	std::fstream fielStrem(str + ".txt", std::ios_base::in | std::ios_base::binary);
	if (!fielStrem.is_open())
	{
		return;
	}

	google::protobuf::io::IstreamInputStream input(&fielStrem);
	t->ParseFromZeroCopyStream(&input);

	std::vector<double> vec(t->f1().size());
	memcpy(vec.data(), t->f1().data(), vec.size() * sizeof(double));
	std::vector<double> vec5(t->f5().size());
	memcpy(vec5.data(), t->f5().data(), vec5.size() * sizeof(double));
	std::vector<google::protobuf::int32> vec8(t->f8().size());
	memcpy(vec8.data(), t->f8().data(), vec8.size() * sizeof(google::protobuf::int32));
	savaFile(t, str + ".dis");
//	std::string * stt = t->mutable_f2()->mutable_f6()->mutable_f1();
	
// 	{
// 		std::fstream fielStrem(str + ".p1", std::ios_base::out | std::ios_base::binary| std::ios_base::trunc);
// 		if (fielStrem.is_open())
// 		{
// 			fielStrem << *stt;
// 			fielStrem.close();
// 		}
// 	}
	
}

int main()
{
	//doS(54455, 425, "C:\\Users\\chenwei\\Desktop\\temp\\zip\\f.txt", "C:\\Users\\chenwei\\Desktop\\temp\\zip\\f7.txt");
	std::string str1 = "C:\\Users\\chenwei\\Desktop\\temp\\zip\\f (10)";
	//guess(str1);
	for (int i = 0; i <= 10; ++i)
	{
		std::string str = "C:\\Users\\chenwei\\Desktop\\temp\\f\\f (" + std::to_string(i) + ")";
		guess(str);
		//UnSerialize("C:\\Users\\chenwei\\Desktop\\temp\\f\\f (" + std::to_string(i) + ").txt", "C:\\Users\\chenwei\\Desktop\\temp\\f\\f (" + std::to_string(i) + ").dec");
	}
	//UnSerialize("D:\\VSProject\\github\\parseProtoBuffer\\parseProtoBuffer\\f20_field_7_size_425", "D:\\VSProject\\github\\parseProtoBuffer\\parseProtoBuffer\\f20_field_7_size_425.dec");
	//doS();
	//doSize();
	//doT();
	return 0;
	std::stringstream strStream;
	tutorial::Student * s = new tutorial::Student;
	std::string str;
	

//	s->maths_size();
// 	s->mutable_maths(0);
// 	s->set_allocated_math(new tutorial::StudentLeader);
// 	s->mutable_math()->set_age(15);


// 	std::fstream fielStrem("123.tt",std::ios_base::out| std::ios_base::binary| std::ios_base::trunc);
// 	fielStrem.is_open();
// 	google::protobuf::io::OstreamOutputStream strea(&fielStrem);
// 	google::protobuf::io::CodedOutputStream outs(&strea);


	s->SerializeToString(&str);
	s->GetMetadata();
	s->GetTypeName();
	
	tutorial::Student * ss = new tutorial::Student;

// 	google::protobuf::io::CodedInputStream decoder(reinterpret_cast<const google::protobuf::uint8*>(str.data()),
// 		str.size());
	//doT(&strea);
	//doT(str);
	ss->ParseFromString(str);
    return 0;
}

