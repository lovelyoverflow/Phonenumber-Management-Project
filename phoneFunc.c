/* Name: phoneFunc.c  ver 1.1
 * Content: 전화번호 컨트롤 함수.
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

/* 함    수: void InputPhoneData(void)
 * 기    능: 전화번호 관련 데이터 입력 받아서 저장. 
 * 반    환: void.
 *
 */

void StoreDataToFileInStruct(void)
{
	int i;

	FILE * fp = fopen("Saved data.sav", "wb");  // 파일 새로 생성.

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

	if (fp == NULL)  // 파일이 존재하지 않는다면.
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

	fputs("이름 입력: ", stdout);
	fgets(phoneList[numOfData]->name, sizeof(phoneList[numOfData]->name), stdin);

	len = strlen(phoneList[numOfData]->name);
	phoneList[numOfData]->name[len - 1] = '\0';

	fputs("전화번호 입력: ", stdout);
	fgets(phoneList[numOfData]->phoneNum, sizeof(phoneList[numOfData]->phoneNum), stdin);

	len = strlen(phoneList[numOfData]->phoneNum);
	phoneList[numOfData]->phoneNum[len - 1] = '\0';

	for (i = 0; i < numOfData; i++)
	{
		if (!strcmp(phoneList[i]->name, phoneList[numOfData]->name))
		{
			if (!strcmp(phoneList[i]->phoneNum, phoneList[numOfData]->phoneNum)) {
				puts("이미 입력된 데이터 입니다.");
				getchar();
				free(phoneList[numOfData]);
				return;
			}
		}
	}
	numOfData++;
	StoreDataToFileInStruct();
}

/* 함	 수: void ShowAllData(void)
 * 기    능: 저장된 데이터 전체 출력. 
 * 반    환: void.
 *
 */
void ShowAllData(void)
{
	int i;

	if (numOfData == 0)
	{
		puts("정보가 존재하지 않습니다.");
		getchar();
		return;
	}
	for (i = 0; i < numOfData; i++)
		ShowPhoneInfoByPtr(phoneList[i]);
	
	puts("출력이 완료되었습니다.");
	getchar();
}

/* 함	 수: void SearchPhoneData(void)
 * 기	 능: 저장된 데이터 검색 후 출력
 * 반	 환: void
 *
 */
void SearchPhoneData(void)
{
	char Search[30];
	int i;
	int cnt = 0;
	int len;

	fputs("찾는 이름은? ", stdout);
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
		puts("대상을 찾을 수 없습니다. ");
		getchar();
	}
	else
		getchar();
}

/* 함	 수: void DeletePhoneData(void)
 * 기	 능: 저장된 데이터 삭제
 * 반	 환: void
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

	fputs("삭제할 이름은? ", stdout);
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

				puts("삭제가 완료되었습니다.");
				getchar();
				return;
			}
		}
	}
	else if (cnt == 0)
	{
		puts("찾는 이름이 없습니다.");
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
			fputs("선택: ", stdout);
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
					puts("삭제가 완료되었습니다.");
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

	fputs("변경할 이름은? ", stdout);
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
				fputs("변경할 전화번호는? ", stdout);
				fgets(phoneList[i]->phoneNum, sizeof(phoneList[i]->phoneNum), stdin);
				StoreDataToFileInStruct();
				return;
			}
		}
	}
	else if (cnt == 0)
	{
		puts("찾는 이름이 없습니다.");
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
		fputs("선택: ", stdout);
		scanf("%d", &sel);
		j = 0;
		for (i = 0; i < numOfData; i++)
		{
				j++;
				if (j == sel)
				{
					j = Sidx[j-1];
					fputs("변경할 전화번호는? ", stdout);
					fgets(phoneList[j]->phoneNum, sizeof(phoneList[j]->phoneNum), stdin);
					StoreDataToFileInStruct();
					return;
				
			}
		}
	}
}
/* end of file */