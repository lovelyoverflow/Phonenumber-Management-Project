#include "common.h"
#include "phoneData.h"

/* 함    수: void ShowMenu(void)
 * 기    능: 선택을 위한 메뉴 출력. 
 * 반    환: void.
 *
 */
void ShowMenu(void)
{
    system("cls");   //stdlib.h
    
    printf("━━━━━ 메  뉴 ━━━━━━━ \n");
    printf(" 1. 전화번호 입력 \n");
    printf(" 2. 전체 정보 출력 \n");
	printf(" 3. 전화번호 검색 \n");
	printf(" 4. 전화번호 삭제 \n");
	printf(" 5. 전화번호 변경 \n");
    printf(" 6. 종료 \n");
    printf("━━━━━━━━━━━━━━━━ \n");
    printf("선택》 ");
}

/* 함    수: void ShowPhoneInfo(phoneData phone)
 * 기    능: 이름과 전화번호 정보 출력.
 * 반    환: void.
 *
 */
void ShowPhoneInfo(phoneData phone)
{    
    printf("┏━━━━━━━━━━━━━━━━ \n"   ); 
    printf("┃ ▶ 이름: %s \n", phone.name           );
    printf("┃ ▶ 전화번호: %s \n", phone.phoneNum   );
    printf("┗━━━━━━━━━━━━━━━━ \n\n" );
}


/* 함	 수: void ShowPhoneInfoByPtr(phoneData * phone)
* 기	 능: 저장된 데이터 전체 출력
* 반	 환: void
*
*/

void ShowPhoneInfoByPtr(phoneData * phone)
{
	printf("┏━━━━━━━━━━━━━━━━ \n");
	printf("┃ ▶ 이름: %s \n", phone->name);
	printf("┃ ▶ 전화번호: %s \n", phone->phoneNum);
	printf("┗━━━━━━━━━━━━━━━━ \n\n");
}
/* end of file */
