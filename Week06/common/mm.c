// /*
//  * mm-naive.c - The fastest, least memory-efficient malloc package.
//  *
//  * In this naive approach, a block is allocated by simply incrementing
//  * the brk pointer.  A block is pure payload. There are no headers or
//  * footers.  Blocks are never coalesced or reused. Realloc is
//  * implemented directly using mm_malloc and mm_free.
//  *
//  * NOTE TO STUDENTS: Replace this header comment with your own header
//  * comment that gives a high level description of your solution.
//  */
// #include <stdio.h>
// #include <stdlib.h>
// #include <assert.h>
// #include <unistd.h>
// #include <string.h>

// #include "mm.h"
// #include "memlib.h"

//  /*********************************************************
//      * NOTE TO STUDENTS: Before you do anything else, please
//      * provide your team information in the following struct.
//      ********************************************************/
// team_t team = {
//     /* Team name */
//     "team",
//     /* First member's full name */
//     "joohwan park",
//     /* First member's email address */
//     "jhpark4947@gmail.com",
//     /* Second member's full name (leave blank if none) */
//     "",
//     /* Second member's email address (leave blank if none) */
//     "" };
// /* Basic constantsand macros*/
// #define WSIZE 4 // word and header footer 사이즈를 byte로. 
// #define DSIZE 8 // double word size를 byte로
// #define CHUNKSIZE (1<<12) // heap을 늘릴 때 얼만큼 늘릴거냐? 4kb 분량.

// #define MAX(x,y) ((x)>(y)? (x) : (y)) // x,y 중 큰 값을 가진다.

// // size를 pack하고 개별 word 안의 bit를 할당 (size와 alloc을 비트연산), 헤더에서 써야하기 때문에 만듬.
// #define PACK(size,alloc) ((size)| (alloc)) // alloc : 가용여부 (ex. 000) / size : block size를 의미. =>합치면 온전한 주소가 나온다.

// /* address p위치에 words를 read와 write를 한다. */
// #define GET(p) (*(unsigned int*)(p)) // 포인터를 써서 p를 참조한다. 주소와 값(값에는 다른 블록의 주소를 담는다.)을 알 수 있다. 다른 블록을 가리키거나 이동할 때 쓸 수 있다. 
// #define PUT(p,val) (*(unsigned int*)(p)=(int)(val)) // 블록의 주소를 담는다. 위치를 담아야지 나중에 헤더나 푸터를 읽어서 이동 혹은 연결할 수 있다.

// // address p위치로부터 size를 읽고 field를 할당
// #define GET_SIZE(p) (GET(p) & ~0x7) // '~'은 역수니까 11111000이 됨. 비트 연산하면 000 앞에거만 가져올 수 있음. 즉, 헤더에서 블록 size만 가져오겠다.
// #define GET_ALLOC(p) (GET(p) & 0x1) // 00000001이 됨. 헤더에서 가용여부만 가져오겠다.

// /* given block ptr bp, header와 footer의 주소를 계산*/
// #define HDRP(bp) ((char*)(bp) - WSIZE) // bp가 어디에있던 상관없이 WSIZE 앞에 위치한다.
// #define FTRP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) // 헤더의 끝 지점부터 GET SIZE(블록의 사이즈)만큼 더한 다음 word를 2번빼는게(그 뒤 블록의 헤드에서 앞으로 2번) footer의 시작 위치가 된다.

// /* GIVEN block ptr bp, 이전 블록과 다음 블록의 주소를 계산*/
// #define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE(((char*)(bp)-WSIZE))) // 그 다음 블록의 bp 위치로 이동한다.(bp에서 해당 블록의 크기만큼 이동 -> 그 다음 블록의 헤더 뒤로 감.)
// #define PREV_BLKP(bp) ((char*)(bp) - GET_SIZE(((char*)(bp) - DSIZE))) // 그 전 블록의 bp위치로 이동.(이전 블록 footer로 이동하면 그 전 블록의 사이즈를 알 수 있으니 그만큼 그 전으로 이동.)
//  // 처음에 쓸 큰 가용블록 힙을 만들어줌.

// /*
//  * mm_init - initialize the malloc package.
//  */
//  //선언하기 

// static void* coalesce(void* bp) {


//     size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
//     size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
//     size_t size = GET_SIZE(HDRP(bp));

//     //case1:직전 직후 블록이 모두 할당 
//     //해당 블로만 
//     if (prev_alloc && next_alloc) {
//         return bp;

//     }

//     //case 2 : 직전 블록 할당 , 직후 블록 가용 
//     else if (prev_alloc && !next_alloc) {
//         size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
//         PUT(HDRP(bp), PACK(size, 0));
//         PUT(FTRP(bp), PACK(size, 0));
//         //블록 포인터는 변경할 필요없다. 
//     }


//     else if (!prev_alloc && next_alloc) {
//         size += GET_SIZE(HDRP(PREV_BLKP(bp)));
//         PUT(FTRP(bp), PACK(size, 0));
//         PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
//         bp = PREV_BLKP(bp);
//         //블록 포인터는 변경할 필요없다. 
//     }

//     else {
//         size += GET_SIZE(HDRP(PREV_BLKP(bp)))
//             + GET_SIZE(FTRP(NEXT_BLKP(bp)));
//         PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
//         PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
//         bp = PREV_BLKP(bp);
//         //블록 포인터는 변경할 필요없다. 
//     }

//     return bp;

// }
// static void* extend_heap(size_t words) {

//     char* bp;
//     size_t size;
//     /*더블 워드 정렬에 따라 메모리르 mem_sbrk 함수를 이용해 할당받음 .mem_sbrk는 힙용량을 늘려줌*/
//     size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;//words가 홀수면 +1을 해서 공간 할당 
//     if ((long) (bp = mem_sbrk(size)) == -1) {
//         return NULL;
//     }
//     /*블록 헤더와 푸터 그리고 에필로그의 헤더를 초기화한다.*/
//     PUT(HDRP(bp), PACK(size, 0));
//     PUT(FTRP(bp), PACK(size, 0));
//     PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));//새 에필로그 헤더 
//     /*extend_heap 블록 너머에 오지 않도록 배치한 블록 다음 공간을 */
//     //만약 이전 블록이 가용 블록이라면 연결 
//     return coalesce(bp);
// }

// static char* heap_listp;

// /*mm_init: 말록패키지를 초기화 */
// int mm_init(void)
// {

//     //빈 힙 초기값을 설정해준다. 
//     if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void*) -1) {

//         return -1;
//     }
//     PUT(heap_listp, 0); //Alignment padding
//     PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));//prologue header 
//     PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));//prologue footet 
//     PUT(heap_listp + (3 * WSIZE), PACK(0, 1));//epiloge header
//     heap_listp += (2 * WSIZE);//정적 전역 변수는 늘 prologue block을 가리킨다. 
//     /* 그후 chunck 사이즈만큼 힙을 확장해 초기 가용 블록을 생성한다. */

//     if (extend_heap(CHUNKSIZE / WSIZE) == NULL) // extend heap을 통해 시작할 때 한번 heap을 늘려줌. 늘리는 양은 상관없음.
//         return -1;
//     return 0;
// }


// /* extena 힙이 사용 경우 */
// //1)힙이 초기화될때
// //2)mm_malloc이 적당한 fit을 찾지 못했을때 

// //extend heap :워드 단위 메모리를 인자로 받아 힙을 늘려준다. 

// //블록을 반환하고 경계태그 연결 사용 - 상수 시간 안에 인접한 가용 블록들과 통합하는 함수 

// void mm_free(void* bp)
// {

//     //해당블록의 size를 알아내 header 와 footer를 수정한다. 
//     size_t size = GET_SIZE(HDRP(bp));//얼만큼 free 해야 하는지 
//     PUT(HDRP(bp), PACK(size, 0)); //header,footer 들을 free 시킨다. 안에 들어있는 걸 지우는게 아니라 가용 상태로 만드는 것이다. 
//     PUT(FTRP(bp), PACK(size, 0));


//     //만약 앞뒤의 블록이 가용상태라면 연결한다. 
//     coalesce(bp);
// }



// //bp = breakpoint
// static void* find_fit(size_t asize) {
//     void* bp;
//     //헤더의 사이즈가 0보다 크다. ->에필로그까지 탐색한다.
//     for (bp = heap_listp;GET_SIZE(HDRP(bp)) > 0;bp = NEXT_BLKP(bp)) {//init에서 쓴 heaplistp를 쓴다. 처음 출발하고 그 다음이 regular block 첫번재 헤더 위치네 
//     //for 문이 계속 돌면 epilogie header 까지 간다. epilogue header는 0이니까 종료된다. 
//         if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) { // 이블록이 가용하고 내가 갖고 있는 asize를 담을 수 있으면 내가 넣을 수 있는 블록만 찾는 거니까 그게 나오면 리턴 
//             return bp;
//         }
//     }
//     return NULL;
// }


// static void place(void* bp, size_t asize) { //들어갈 위치를 포인터로 받는다. (find fit에서 찾는 bp) 크기는 asize로 받음 
//     size_t csize = GET_SIZE(HDRP(bp));//현재 있는 블록의 사이즈 
//     if ((csize - asize) >= (2 * DSIZE)) { //현재 있는 블록 사이즈에서 asize를 넣어도 헤어푸터 있는 최소 사이즈 보다 남냐 남으면 다른 데이터 더 넣을 수 있으니까 
//         PUT(HDRP(bp), PACK(asize, 1)); //헤더위치에 aszie만큼 넣고 1로 상태변환 원래 헤더 사이즈에서 지금 넣으려고 하는 사이즈로 갱신 (자르는 효과 )
//         PUT(FTRP(bp), PACK(asize, 1));//푸터 위치도 변경 
//         bp = NEXT_BLKP(bp);//regular 블록 만큼 하나 이동해서 bp위치 갱신 
//         //나머지를 가용블럭으로 만들어 준다. 
//         PUT(HDRP(bp), PACK(csize - asize, 0)); //나머지 블록은 다 가용하다 (0값을 넎어준다.)
//         PUT(FTRP(bp), PACK(csize - asize, 0));
//     }//csize의 만큼의 크기 밖에 없을 경우 
//     else {
//         PUT(HDRP(bp), PACK(csize, 1));//위의 조건이 아니면 asize만 csize에 들어갈 수 있기 때문에 내가 다 먹는다. 
//         PUT(FTRP(bp), PACK(csize, 1));


//     }
// }
// void* mm_malloc(size_t size)
// {
//     size_t asize; // 블록사이즈를 조정한다. 
//     size_t extendsize;//fit이 없으면 heap을 늘려준다.
//     char* bp;


//     /* 거짓된 요청 무시*/
//     if (size == 0) return NULL; // 인자로 받은 size가 0이니까 할당할 필요 없음.

//     if (size <= DSIZE) {
//         asize = 2 * DSIZE;
//     }
//     else {
//         asize = DSIZE * ((size + (DSIZE) +(DSIZE - 1)) / DSIZE);
//     }
//     //서치 더 프리 리스트
//     if ((bp = find_fit(asize)) != NULL) {
//         place(bp, asize);
//         return bp;
//     }

//     //fit이 아예 발견되지 않았을때 메모리를 더 가져오고 블럭을 위치시킨다.
//     extendsize = MAX(asize, CHUNKSIZE);
//     if ((bp = extend_heap(extendsize / WSIZE)) == NULL) {
//         return NULL;
//     }
//     place(bp, asize);
//     return bp;
// }

// /*
//  * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
//  */
// void* mm_realloc(void* ptr, size_t size)
// {
//     void* oldptr = ptr;
//     void* newptr;
//     size_t copySize;

//     newptr = mm_malloc(size);
//     if (newptr == NULL)
//         return NULL;
//     copySize = GET_SIZE(HDRP(oldptr));
//     if (size < copySize)
//         copySize = size;
//     memcpy(newptr, oldptr, copySize);
//     mm_free(oldptr);
//     return newptr;
// }


//next fit

/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

 /*********************************************************
     * NOTE TO STUDENTS: Before you do anything else, please
     * provide your team information in the following struct.
     ********************************************************/
team_t team = {
    /* Team name */
    "team",
    /* First member's full name */
    "joohwan park",
    /* First member's email address */
    "jhpark4947@gmail.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    "" };
/* Basic constantsand macros*/
#define WSIZE 4 // word and header footer 사이즈를 byte로. 
#define DSIZE 8 // double word size를 byte로
#define CHUNKSIZE (1<<12) // heap을 늘릴 때 얼만큼 늘릴거냐? 4kb 분량.

#define MAX(x,y) ((x)>(y)? (x) : (y)) // x,y 중 큰 값을 가진다.

// size를 pack하고 개별 word 안의 bit를 할당 (size와 alloc을 비트연산), 헤더에서 써야하기 때문에 만듬.
#define PACK(size,alloc) ((size)| (alloc)) // alloc : 가용여부 (ex. 000) / size : block size를 의미. =>합치면 온전한 주소가 나온다.

/* address p위치에 words를 read와 write를 한다. */
#define GET(p) (*(unsigned int*)(p)) // 포인터를 써서 p를 참조한다. 주소와 값(값에는 다른 블록의 주소를 담는다.)을 알 수 있다. 다른 블록을 가리키거나 이동할 때 쓸 수 있다. 
#define PUT(p,val) (*(unsigned int*)(p)=(int)(val)) // 블록의 주소를 담는다. 위치를 담아야지 나중에 헤더나 푸터를 읽어서 이동 혹은 연결할 수 있다.

// address p위치로부터 size를 읽고 field를 할당
#define GET_SIZE(p) (GET(p) & ~0x7) // '~'은 역수니까 11111000이 됨. 비트 연산하면 000 앞에거만 가져올 수 있음. 즉, 헤더에서 블록 size만 가져오겠다.
#define GET_ALLOC(p) (GET(p) & 0x1) // 00000001이 됨. 헤더에서 가용여부만 가져오겠다.

/* given block ptr bp, header와 footer의 주소를 계산*/
#define HDRP(bp) ((char*)(bp) - WSIZE) // bp가 어디에있던 상관없이 WSIZE 앞에 위치한다.
#define FTRP(bp) ((char*)(bp) + GET_SIZE(HDRP(bp)) - DSIZE) // 헤더의 끝 지점부터 GET SIZE(블록의 사이즈)만큼 더한 다음 word를 2번빼는게(그 뒤 블록의 헤드에서 앞으로 2번) footer의 시작 위치가 된다.

/* GIVEN block ptr bp, 이전 블록과 다음 블록의 주소를 계산*/
#define NEXT_BLKP(bp) ((char*)(bp) + GET_SIZE(((char*)(bp)-WSIZE))) // 그 다음 블록의 bp 위치로 이동한다.(bp에서 해당 블록의 크기만큼 이동 -> 그 다음 블록의 헤더 뒤로 감.)
#define PREV_BLKP(bp) ((char*)(bp) - GET_SIZE(((char*)(bp) - DSIZE))) // 그 전 블록의 bp위치로 이동.(이전 블록 footer로 이동하면 그 전 블록의 사이즈를 알 수 있으니 그만큼 그 전으로 이동.)
 // 처음에 쓸 큰 가용블록 힙을 만들어줌.

/*
 * mm_init - initialize the malloc package.
 */
 //선언하기 
static char* heap_listp = NULL;
char* start_nextfit = NULL; //nextfit은 움직이니까 static으로 하면 안된다. 

static void* coalesce(void* bp) {


    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    //case1:직전 직후 블록이 모두 할당 
    //해당 블로만 
    if (prev_alloc && next_alloc) {
        start_nextfit = bp;

        return bp;

    }

    //case 2 : 직전 블록 할당 , 직후 블록 가용 
    else if (prev_alloc && !next_alloc) {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        //블록 포인터는 변경할 필요없다. 
    }


    else if (!prev_alloc && next_alloc) {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(FTRP(bp), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
        //블록 포인터는 변경할 필요없다. 
    }

    else {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)))
            + GET_SIZE(FTRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
        //블록 포인터는 변경할 필요없다. 
    }
    start_nextfit = bp;
    return bp;

}
static void* extend_heap(size_t words) {

    char* bp;
    size_t size;
    /*더블 워드 정렬에 따라 메모리르 mem_sbrk 함수를 이용해 할당받음 .mem_sbrk는 힙용량을 늘려줌*/
    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;//words가 홀수면 +1을 해서 공간 할당 
    if ((long) (bp = mem_sbrk(size)) == -1) {
        return NULL;
    }
    /*블록 헤더와 푸터 그리고 에필로그의 헤더를 초기화한다.*/
    PUT(HDRP(bp), PACK(size, 0));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));//새 에필로그 헤더 
    /*extend_heap 블록 너머에 오지 않도록 배치한 블록 다음 공간을 */
    //만약 이전 블록이 가용 블록이라면 연결 
    return coalesce(bp);
}



/*mm_init: 말록패키지를 초기화 */
int mm_init(void)
{

    //빈 힙 초기값을 설정해준다. 
    if ((heap_listp = mem_sbrk(4 * WSIZE)) == (void*) -1) {

        return -1;
    }
    PUT(heap_listp, 0); //Alignment padding
    PUT(heap_listp + (1 * WSIZE), PACK(DSIZE, 1));//prologue header 
    PUT(heap_listp + (2 * WSIZE), PACK(DSIZE, 1));//prologue footet 
    PUT(heap_listp + (3 * WSIZE), PACK(0, 1));//epiloge header
    heap_listp += (2 * WSIZE);//정적 전역 변수는 늘 prologue block을 가리킨다. 
    start_nextfit = heap_listp;
    /* 그후 chunck 사이즈만큼 힙을 확장해 초기 가용 블록을 생성한다. */


    if (extend_heap(CHUNKSIZE / WSIZE) == NULL) // extend heap을 통해 시작할 때 한번 heap을 늘려줌. 늘리는 양은 상관없음.
        return -1;
    return 0;
}


/* extena 힙이 사용 경우 */
//1)힙이 초기화될때
//2)mm_malloc이 적당한 fit을 찾지 못했을때 

//extend heap :워드 단위 메모리를 인자로 받아 힙을 늘려준다. 

//블록을 반환하고 경계태그 연결 사용 - 상수 시간 안에 인접한 가용 블록들과 통합하는 함수 

void mm_free(void* bp)
{

    //해당블록의 size를 알아내 header 와 footer를 수정한다. 
    size_t size = GET_SIZE(HDRP(bp));//얼만큼 free 해야 하는지 
    PUT(HDRP(bp), PACK(size, 0)); //header,footer 들을 free 시킨다. 안에 들어있는 걸 지우는게 아니라 가용 상태로 만드는 것이다. 
    PUT(FTRP(bp), PACK(size, 0));


    //만약 앞뒤의 블록이 가용상태라면 연결한다. 
    coalesce(bp);
}



//bp = breakpoint
static void* find_fit(size_t asize) {
    void* bp;

    for (bp = start_nextfit;GET_SIZE(HDRP(bp)) > 0;bp = NEXT_BLKP(bp)) {

        if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) {
            start_nextfit = bp;
            return bp;
        }
    }

    for (bp = heap_listp; bp < start_nextfit;bp = NEXT_BLKP(bp)) {
        //for 문이 계속 돌면 epilogie header 까지 간다. epilogue header는 0이니까 종료된다. 
        if (!GET_ALLOC(HDRP(bp)) && (asize <= GET_SIZE(HDRP(bp)))) { // 이블록이 가용하고 내가 갖고 있는 asize를 담을 수 있으면 내가 넣을 수 있는 블록만 찾는 거니까 그게 나오면 리턴 
            start_nextfit = bp;
            return bp;
        }
    }
    return NULL;
}


static void place(void* bp, size_t asize) { //들어갈 위치를 포인터로 받는다. (find fit에서 찾는 bp) 크기는 asize로 받음 
    size_t csize = GET_SIZE(HDRP(bp));//현재 있는 블록의 사이즈 
    if ((csize - asize) >= (2 * DSIZE)) { //현재 있는 블록 사이즈에서 asize를 넣어도 헤어푸터 있는 최소 사이즈 보다 남냐 남으면 다른 데이터 더 넣을 수 있으니까 
        PUT(HDRP(bp), PACK(asize, 1)); //헤더위치에 aszie만큼 넣고 1로 상태변환 원래 헤더 사이즈에서 지금 넣으려고 하는 사이즈로 갱신 (자르는 효과 )
        PUT(FTRP(bp), PACK(asize, 1));//푸터 위치도 변경 
        bp = NEXT_BLKP(bp);//regular 블록 만큼 하나 이동해서 bp위치 갱신 
        //나머지를 가용블럭으로 만들어 준다. 
        PUT(HDRP(bp), PACK(csize - asize, 0)); //나머지 블록은 다 가용하다 (0값을 넎어준다.)
        PUT(FTRP(bp), PACK(csize - asize, 0));
    }//csize의 만큼의 크기 밖에 없을 경우 
    else {
        PUT(HDRP(bp), PACK(csize, 1));//위의 조건이 아니면 asize만 csize에 들어갈 수 있기 때문에 내가 다 먹는다. 
        PUT(FTRP(bp), PACK(csize, 1));


    }
}
void* mm_malloc(size_t size)
{
    size_t asize; // 블록사이즈를 조정한다. 
    size_t extendsize;//fit이 없으면 heap을 늘려준다.
    char* bp;


    /* 거짓된 요청 무시*/
    if (size == 0) return NULL; // 인자로 받은 size가 0이니까 할당할 필요 없음.

    if (size <= DSIZE) {
        asize = 2 * DSIZE;
    }
    else {
        asize = DSIZE * ((size + (DSIZE) +(DSIZE - 1)) / DSIZE);
    }
    //서치 더 프리 리스트
    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    //fit이 아예 발견되지 않았을때 메모리를 더 가져오고 블럭을 위치시킨다.
    extendsize = MAX(asize, CHUNKSIZE);
    if ((bp = extend_heap(extendsize / WSIZE)) == NULL) {
        return NULL;
    }
    place(bp, asize);
    return bp;
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
 // void* mm_realloc(void* ptr, size_t size) //size가 새로운 사이즈임 
 // {
 //     void* oldptr = ptr;
 //     void* newptr;
 //     size_t copySize;

 //     newptr = mm_malloc(size);
 //     if (newptr == NULL)
 //         return NULL;
 //     copySize = GET_SIZE(HDRP(oldptr));
 //     if (size < copySize)
 //         copySize = size;
 //     if (size > copySize)
 //         copySize = size;
 //     memcpy(newptr, oldptr, copySize);
 //     mm_free(oldptr);
 //     return newptr;
 // }
void* mm_realloc(void* ptr, size_t size) //size가 새로운 사이즈임 
{
    size_t old_size = GET_SIZE(HDRP(ptr));
    size_t new_size = size + (2 * WSIZE); //헤더와 푸터 더해줌
    if (new_size <= old_size) {
        return ptr;
    }
    else {
        size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(ptr))); //다음 블록의 가용상태 확인 
        size_t current_size = old_size + GET_SIZE(HDRP(NEXT_BLKP(ptr)));
        if (!next_alloc && current_size >= new_size) {
            PUT(HDRP(ptr), PACK(current_size, 1));
            PUT(FTRP(ptr), PACK(current_size, 1));
            return ptr;
        }
        else {
            void* new_bp = mm_malloc(new_size);
            memcpy(new_bp, ptr, new_size); // 새로운 할당 블록에 ptr부터 new_size까지의 크기의 블록 할당
            mm_free(ptr);
            return new_bp;
        }
    }

}