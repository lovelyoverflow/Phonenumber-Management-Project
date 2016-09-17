/* Name: main.c  ver 1.0
 * Content: main �Լ�.
 * Implementation: YSW
 * 
 * Last modified 2008/01/01
 */

#include "common.h"
#include "screenOut.h"
#include "phoneFunc.h"

enum{INPUT=1, SHOWALL, SEARCH, DELETE, CHANGE, QUIT};

/* ��    ��: int main (void)
 * ��    ��: ����� ���� ó��. 
 * ��    ȯ: ���� ����� 0.
 *
 */
int main(void)
{  
    int inputMenu = 0;
    
	LoadDataFromFileInStruct();
    while(1)
    {
        ShowMenu();
        fputs("�����ϼ��� : ", stdout);
        scanf("%d", &inputMenu);
		getchar();
  		        
        switch(inputMenu)
        {
        case INPUT:
            InputPhoneData();
            break;
        
        case SHOWALL:
            ShowAllData();
            break;

		case SEARCH:
			SearchPhoneData();
			break;

		case DELETE:
			DeletePhoneData();
			break;

		case CHANGE:
			ChangePhoneData();
			break;
        }
        
        if(inputMenu==QUIT)
        {
            puts("�̿��� �ּż� ������~");
			StoreDataToFileInStruct();
            break;
        }
    }    
	return 0;
}

/* end of file */