#pragma once
class Eva
{
public:
	Eva()
	{
		printf("�G���@�N��\n");
	};
	~Eva()
	{
		printf("�������E\n");
	};
};
class EntryPlug
{
public:
	EntryPlug()
	{
		printf("�G���g���[�v���O�}��\n");
	};
	~EntryPlug()
	{
		printf("�G���g���[�v���O���E\n");
	};
};
class Cable
{
public:
	Cable()
	{
		printf("�A���r���J���P�[�u���f��\n");
	};
	~Cable()
	{
		printf("�������E�܂ł���4��53�b\n");
	};
};
class Shito
{
public:
	Shito()
	{
		printf("�g�k�ƌ�풆\n");
	};
	~Shito()
	{
		printf("�g�k���j\n");
	};
};
void test()
{
	EntryPlug plug;
	Eva eva;
	Shito shito;
	Cable cable;
}