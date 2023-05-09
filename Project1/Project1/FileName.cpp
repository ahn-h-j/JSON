#include <iostream>
#include <fstream>

#include "json/json.h"
#include "json/json-forwards.h"
#include "jsoncpp.cpp"



using namespace std;

void jsonWrite() {
	ofstream json_file;
	json_file.open("C:\JSON_DATA.json");

	Json::Value Computer;
	Computer["CPU"] = "I7";
	Computer["RAM"] = "16G";

	Json::Value Language;
	Language["C++"] = "Visual Studio";
	Language["Python"] = "IDLE";

	Computer["Program"] = Language;
	Computer["HDD"] = "2TB";

	Json::Value Cable;
	Cable.append("Power");
	Cable.append("Printer");
	Cable.append("Mouse");

	Computer["Computer"]["Cable"] = Cable;

	Json::Value number;
	number["Int"] = 123;
	number["Double"] = 456.012;
	number["Bool"] = true;

	Computer["Computer"]["Number"] = number;

	Json::StreamWriterBuilder builder;
	builder["commentStyle"] = "None";
	builder["indentation"] = "    ";  // Tab
	unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

	// ���ĺ� ������ write �ȴ�.
	writer->write(Computer, &cout);
	writer->write(Computer, &json_file);
	cout << endl;  // add lf and flush

	json_file.close();
}

void jsonRead() {
	ifstream json_dir("C:\JSON_DATA.json");
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;
	Json::Value value;

	JSONCPP_STRING errs;
	bool ok = parseFromStream(builder, json_dir, &value, &errs);

	if (ok == true)
	{
		cout << "CPU: " << value["CPU"] << endl;
		cout << "Program Python: " << value["Program"]["Python"] << endl;
		cout << "Computer Cable: " << value["Computer"]["Cable"] << endl;
		cout << "Computer Cable[0]: " << value["Computer"]["Cable"][0] << endl;
		cout << endl;

		cout << "Computer Number Int(as int): " << value["Computer"]["Number"].get("Int", -1).asInt() << endl;
		// "Int" ���� ������ -1 ��ȯ.
		cout << "Computer Number Int(as int): " << value["Computer"]["Number"]["Int"].asInt() << endl;
		// "Int" ���� ������ 0 ��ȯ.
		cout << "Computer Number Double(as double): " << value["Computer"]["Number"].get("Double", -1).asDouble() << endl;
		// "Double" ���� ������ -1 ��ȯ.
		cout << "Computer Number Double(as string): " << value["Computer"]["Number"].get("Double", "Empty").asString() << endl;
		// "Double" ���� ������ Empty ��ȯ.
		cout << "Computer Number Bool(as bool): " << value["Computer"]["Number"].get("Bool", false).asBool() << endl;
		// "Bool" ���� ������ false ��ȯ.
		cout << endl;

		cout << "Root size: " << value.size() << endl;
		cout << "Program size: " << value["Program"].size() << endl;
		cout << "Computer Cable size: " << value["Computer"]["Cable"].size() << endl;
		cout << endl;

		int size = value["Computer"]["Cable"].size();
		// size() ���� for ������ �״�� ���ϸ� warning C4018�� �߻� �Ѵ�.
		for (int i = 0; i < size; i++)
			cout << "Computer Cable: " << value["Computer"]["Cable"][i] << endl;
		cout << endl;

		for (auto i : value["Computer"]["Cable"])
			cout << "Computer Cable: " << i << endl;
	}
	else
	{
		cout << "Parse failed." << endl;
	}

}

void main() {
	printf("Json ���� ����\n");
	jsonWrite();
	printf("\n\nJson ���� �б�\n");
	jsonRead();
}