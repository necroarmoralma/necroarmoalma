#pragma once
class Eva
{
public:
	Eva()
	{
		printf("エヴァ起動\n");
	};
	~Eva()
	{
		printf("活動限界\n");
	};
};
class EntryPlug
{
public:
	EntryPlug()
	{
		printf("エントリープラグ挿入\n");
	};
	~EntryPlug()
	{
		printf("エントリープラグ離脱\n");
	};
};
class Cable
{
public:
	Cable()
	{
		printf("アンビリカルケーブル断線\n");
	};
	~Cable()
	{
		printf("活動限界まであと4分53秒\n");
	};
};
class Shito
{
public:
	Shito()
	{
		printf("使徒と交戦中\n");
	};
	~Shito()
	{
		printf("使徒撃破\n");
	};
};
void test()
{
	EntryPlug plug;
	Eva eva;
	Shito shito;
	Cable cable;
}