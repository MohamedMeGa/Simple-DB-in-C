/************************************************************/
/**********	Description : LinkedList DRIVER	*****************/
/********** AUTHOR      : Mohamed	MeGa  *******************/
/**********	DATE        : 25 MAR 2022 ***********************/
/**********	VERSION     : V02 *******************************/
/************************************************************/

typedef struct CoursesIDList{
	u8 course1_ID;
	u8 course2_ID;
	u8 course3_ID;
}CoursesID;

typedef struct CoursesGradeList{
	
	u8 course1_Grade;
	u8 course2_Grade;
	u8 course3_Grade;
}CoursesGrade;


typedef struct StudentNodes{
	u8 ID;
	u8 Year;
	CoursesID	* CoursesIDs;
	CoursesGrade* Grades;
	Student 	* Next;
}Student;



typedef struct ListStruct{
	u8 size;
	Student * Head;
}SimpleDB;




void SDB_voidInit(SimpleDB * DB)
{
	DB = (Student *)Calloc(10, sizeof(Student));
	DB -> size = 0;
	DB -> Head = NULL;
}



u8 SDB_u8GetUsedSize(SimpleDB * DB)
{
	return DB->size;
}



u8 SDB_charAddEntry(SimpleDB * DB,u8 id, u8 year, u8 * subjects, u8 * grade)
{
	u8 returnStatus = 0;
	Student * q = DB->Head;
	
	Student * p 			= (Student *)malloc(sizeof(Student));
	CoursesID * couID 		= (CoursesID *)malloc(sizeof(CoursesID));
	CoursesGrade * couGrad 	= (CoursesGrade *)malloc(sizeof(CoursesGrade));
	
	couID->course1_ID = subjects[0];
	couID->course2_ID = subjects[1];
	couID->course3_ID = subjects[2];
	
	couGrad->course1_Grade = grade[0];
	couGrad->course2_Grade = grade[1];
	couGrad->course3_Grade = grade[2];
	
	p->ID = id;
	p->Year = year;
	p->CoursesIDs = couID;
	p->Grades = couGrad;
	
	
	
	//Insert into Head as a first element
	if(DB->size == 0)
	{
		DB->Head = p;
		DB->Head->Next = NULL;
		DB->size++;
		returnStatus = 1;
	}else if(DB->size < 10)
	{
		for(u8 i=0; i < DB->size-1; i++)
		{
			q = q->Next;
		}
		p->Next = q->Next;
		q->Next = p;
		DB->size++;
		returnStatus = 1;
	}else
	{
		returnStatus = 0;
	}
	
	return returnStatus;
	
}












void SDB_voidDeleteStudent(SimpleDB * DB,u8 id)
{
	Student * q = DB->Head;
	if(DB->Head->ID == id)		//if Student Id is first Element
	{
		q = DB->Head->Next;
		DB->Head = q;
		DB->size--;
	}else
	{
		if(SDB_u8IsIdExist)
		{
			while(q->ID != id)
			{
				q = q->Next;
			}
			Student * temp = q->Next->Next;
			free(q->Next);
			free(q->Next->CoursesIDs);
			free(q->Next->Grades);
			q->Next = temp;
			DB->size--;
		}
	}
	
}






u8 SDB_u8tReadEntry(SimpleDB * DB, u8 id, u8 * year, u8 * subject, u8 * grads)
{
	u8 returnStatus = 0;
	Student * q = DB->Head;
	if(DB->Head->ID == id)		//if Student Id is first Element
	{
		year 		= DB->Head->Year;
		subjects 	= DB->Head-> CoursesIDs;
		grads 		= DB->Head-> Grades;
		returnStatus = 1;
	}else
	{
		if(SDB_u8IsIdExist){
			while(q->ID != id)
			{
				q = q->Next;
			}
			q = q->Next;
			year 		= q-> Year;
			subjects 	= q-> CoursesIDs;
			grads 		= q-> Grades;
			returnStatus = 1;
		}else
		{
			returnStatus = 0;
		}
	}
	
	return returnStatus;
}


void SDB_voidGetIdList(SimpleDB * DB, u8 * count, u8 * list)
{
	Student * q = DB->Head;
	count = DB->size;
	for(u8 i=0; i < DB->size; i++)
	{
		list[i] = q->ID;
		q = q->Next;
	}
}


u8 SDB_u8IsIdExist(SimpleDB * DB, u8 id)
{
	u8 returnStatus = 0;
	Student * q = DB->Head;
	
	for(u8 i=0, i < DB->size; i++)
	{
		if(q->ID == id)
		{
			returnStatus = 1;
			break;
		}	
		else
		{
			returnStatus = 0;
		}
		
		q = q->Next;
	}
	return returnStatus;
}