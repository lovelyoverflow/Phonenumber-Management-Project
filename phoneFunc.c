/* Name: phoneFunc.c  ver 1.1
 * Content: ��ȭ��ȣ ��Ʈ�� �Լ�.
 * Implementation: YSW
 * 
 * Last modified 2016/03/26
 */

#include "common.h"
#include "phoneData.h"
#include "screenOut.h"

#define LIST_NUM   100

int numOfData=0;
phoneData * phoneList[LIST_NUM];

/* ��    ��: void InputPhoneData(void)
 * ��    ��: ��ȭ��ȣ ���� ������ �Է� �޾Ƽ� ����. 
 * ��    ȯ: void.
 *
 */

void StoreDataToFileInStruct(void)
{
	int i;

	FILE * fp = fopen("Saved data.sav", "wb");  // ���� ���� ����.

	fwrite(&numOfData, sizeof(int), 1, fp);

	for (i = 0; i<numOfData; i++)
	{
		fwrite(phoneList[i], sizeof(phoneData), 1, fp);
	}

	fclose(fp);
}

void LoadDataFromFileInStruct(void)
{
	int i;

	FILE * fp = fopen("Saved data.sav", "rb");

	if (fp == NULL)  // ������ �������� �ʴ´ٸ�.
		return;

	fread(&numOfData, sizeof(int), 1, fp);

	for (i = 0; i<numOfData; i++)
	{
		phoneList[i] = (phoneData*)malloc(sizeof(phoneData));
		fread(phoneList[i], sizeof(phoneData), 1, fp);
	}
	fclose(fp);
}

void InputPhoneData(void)
{
	int i;
	int len;

	phoneList[numOfData] = (phoneData*)malloc(sizeof(phoneData));

	fputs("�̸� �Է�: ", stdout);
	fgets(phoneList[numOfData]->name, sizeof(phoneList[numOfData]->name), stdin);

	len = strlen(phoneList[numOfData]->name);
	phoneList[numOfData]->name[len - 1] = '\0';

	fputs("��ȭ��ȣ �Է�: ", stdout);
	fgets(phoneList[numOfData]->phoneNum, sizeof(phoneList[numOfData]->phoneNum), stdin);

	len = strlen(phoneList[numOfData]->phoneNum);
	phoneList[numOfData]->phoneNum[len - 1] = '\0';

	for (i = 0; i < numOfData; i++)
	{
		if (!strcmp(phoneList[i]->name, phoneList[numOfData]->name))
		{
			if (!strcmp(phoneList[i]->phoneNum, phoneList[numOfData]->phoneNum)) {
				puts("�̹� �Էµ� ������ �Դϴ�.");
				getchar();
				free(phoneList[numOfData]);
				return;
			}
		}
	}
	numOfData++;
	StoreDataToFileInStruct();
}

/* ��	 ��: void ShowAllData(void)
 * ��    ��: ����� ������ ��ü ���. 
 * ��    ȯ: void.
 *
 */
void ShowAllData(void)
{
	int i;

	if (numOfData == 0)
	{
		puts("������ �������� �ʽ��ϴ�.");
		getchar();
		return;
	}
	for (i = 0; i < numOfData; i++)
		ShowPhoneInfoByPtr(phoneList[i]);
	
	puts("����� �Ϸ�Ǿ����ϴ�.");
	getchar();
}

/* ��	 ��: void SearchPhoneData(void)
 * ��	 ��: ����� ������ �˻� �� ���
 * ��	 ȯ: void
 *
 */
void SearchPhoneData(void)
{
	char Search[30];
	int i;
	int cnt = 0;
	int len;

	fputs("ã�� �̸���? ", stdout);
	fgets(Search, sizeof(Search), stdin);

	len = strlen(Search);

	Search[len - 1] = '\0';

	for (i = 0; i < numOfData; i++)
	{
		if (!strcmp(Search, phoneList[i]->name)) 
		{
			ShowPhoneInfoByPtr(phoneList[i]);
			cnt++;
		}
		
	}
	
	if (cnt == 0)
	{
		puts("����� ã�� �� �����ϴ�. ");
		getchar();
	}
	else
		getchar();
}

/* ��	 ��: void DeletePhoneData(void)
 * ��	 ��: ����� ������ ����
 * ��	 ȯ: void
 *
 */

void DeletePhoneData(void)
{
	char Search[30];
	int i, j;
	int cnt = 0;
	int sel;
	int Sidx[100];
	int len;

	fputs("������ �̸���? ", stdout);
	fgets(Search, sizeof(Search), stdin);

	len = strlen(Search);

	Search[len - 1] = '\0';

	for (i = 0; i < numOfData; i++)
	{
		if (!strcmp(Search, phoneList[i]->name))
		{
			Sidx[cnt++] = i;
		}
	}

	if (cnt == 1)
	{

		for (i = 0; i < numOfData; i++)
		{
			if (!strcmp(Search, phoneList[i]->name))
			{
				for (j = i; j < numOfData - 1; j++)
				{
					phoneList[j] = phoneList[j + 1];
				}
				numOfData--;

				puts("������ �Ϸ�Ǿ����ϴ�.");
				getchar();
				return;
			}
		}
	}
	else if (cnt == 0)
	{
		puts("ã�� �̸��� �����ϴ�.");
		getchar();
	}
	else
	{
		j = 0;
		for (i = 0; i < numOfData; i++)
		{
			if (!strcmp(Search, phoneList[i]->name))
			{

				printf("NUM. %d \n", j + 1);
				ShowPhoneInfoByPtr(phoneList[i]);
				j++;
			}
		}
			fputs("����: ", stdout);
			scanf("%d", &sel);
		j = 0;
		for (i = 0; i < numOfData; i++)
		{
			if (!strcmp(Search, phoneList[i]->name))
			{

				j++;
				if (j == sel)
				{
					phoneList[i] = phoneList[i + 1];
					numOfData--;
					StoreDataToFileInStruct();
					puts("������ �Ϸ�Ǿ����ϴ�.");
					getchar();
					getchar();
				}
			}
		}
	}
}

void StoreDataToFile(void)
{
	FILE * fp = fopen("Saved data.sav", "wb");
	int i;

	fwrite(&numOfData, sizeof(int), 1, fp);

	for (i = 0; i < numOfData; i++)
	{
		fprintf(fp, "%s\n%s\n", phoneList[i]->name, phoneList[i]->phoneNum);

		free(phoneList[i]);
	}

	fclose(fp);
}

void LoadDataFromFile(void)
{
	FILE * fp = fopen("Saved data.sav", "r");
	int i=0;
	int len;

	if (fp == NULL)
		return;

	fread(&numOfData, sizeof(int), 1, fp);

	for (i = 0; i < numOfData; i++)
	{
		phoneList[i] = (phoneData*)malloc(sizeof(phoneData));

		fgets(phoneList[i]->name, NAME_LEN, fp);
		len = strlen(phoneList[i]->name);
		phoneList[i]->name[len - 1] = '\0';

		fgets(phoneList[i]->phoneNum, PHONE_LEN, fp);
		len = strlen(phoneList[i]->phoneNum);
		phoneList[i]->phoneNum[len - 1] = '\0';
	}

	fclose(fp);
}

void ChangePhoneData(void)
{
	char Search[30];
	int Sidx[100];
	int i, j;
	int cnt = 0;
	int sel;
	int len;

	fputs("������ �̸���? ", stdout);
	fgets(Search, sizeof(Search), stdin);

	len = strlen(Search);

	Search[len - 1] = '\0';

	for (i = 0; i < numOfData; i++)
	{
		if (!strcmp(Search, phoneList[i]->name))
		{
			cnt++;
			Sidx[cnt - 1] = i;
		}
	}

	if (cnt == 1)
	{

		for (i = 0; i < numOfData; i++)
		{
			if (!strcmp(Search, phoneList[i]->name))
			{
				fputs("������ ��ȭ��ȣ��? ", stdout);
				fgets(phoneList[i]->phoneNum, sizeof(phoneList[i]->phoneNum), stdin);
				StoreDataToFileInStruct();
				return;
			}
		}
	}
	else if (cnt == 0)
	{
		puts("ã�� �̸��� �����ϴ�.");
		getchar();
	}
	else
	{
		j = 0;
		for (i = 0; i < numOfData; i++)
		{
			if (!strcmp(Search, phoneList[i]->name))
			{

				printf("NUM. %d \n", j + 1);
				ShowPhoneInfoByPtr(phoneList[i]);
				j++;
			}
		}
		fputs("����: ", stdout);
		scanf("%d", &sel);
		j = 0;
		for (i = 0; i < numOfData; i++)
		{
				j++;
				if (j == sel)
				{
					j = Sidx[j-1];
					fputs("������ ��ȭ��ȣ��? ", stdout);
					fgets(phoneList[j]->phoneNum, sizeof(phoneList[j]->phoneNum), stdin);
					StoreDataToFileInStruct();
					return;
				
			}
		}
	}
}
/* end of file */