#include "analyzer.h"
#include"Token.h"
#include <string>
#include <vector>
#include <fstream>
//����ڵ�����
typedef enum {ProK,PheadK,TypeK,VarK,ProcDecK,StmLK,DecK,StmtK,ExpK,ProcK}
              NodeKind;
//���������ڵ�ľ�������
typedef enum {ArrayK,CharK,IntegerK,RecordK,IdK}  DecKind;
// ��������VarKind���͵�ö�ٶ���:           
// ��ʶ��IdV,�����ԱArrayMembV,���ԱFieldMembV
typedef enum {IdV,ArrayMembV,FieldMembV} VarKind; 
//��������ڵ������
typedef enum {IfK,WhileK,AssignK,ReadK,WriteK,CallK,ReturnK} StmtKind;
// ���ʽ����ExpKind���͵�ö�ٶ���:         
typedef enum {OpK,ConstK,VariK} ExpKind;

// ���ͼ��ExpType���͵�ö�ٶ���:
//��Void,��������Integer,�ַ�����Char     
typedef enum {Void,Integer,Boolean} ExpType;

// ��������ParamType���͵�ö�ٶ��壺        
// ֵ��valparamType,���varparamType        
typedef enum {valparamType,varparamType} ParamType;
//�﷨���ڵ� 
typedef struct treeNode

   { 
	 struct treeNode * child[3];	//�ӽڵ�ָ��				
     struct treeNode * sibling;	//�ֵܽڵ�ָ��
     int lineno;		//Դ�����к�
     NodeKind nodekind;	//�ڵ�����
	 int idnum; //��ʶ������
	 string name[20];//��ʶ����

     union 
	 {
		 DecKind  dec;
	     StmtKind stmt; 
		 ExpKind  exp; 
	 } kind;//��������

	 

	 struct 
	 {
		struct
			{	
				int low;              //�����½�
				int up;               // �����Ͻ�
				DecKind   childtype;  // �����������
			}ArrayAttr;               //��������
	         
		struct
			{	
				ParamType  paramt;     //��������
			}ProcAttr;                 //�������� 
		
		struct
			{
				TokenType op; //���ʽ�Ĳ�����						
				int val;		      //���ʽ��ֵ
				VarKind  varkind;     // ���������
				ExpType type;         // �������ͼ��
			}ExpAttr;	           //���ʽ���� 

      char type_name[10];        //�������Ǳ�ʶ��     
             
	 } attr;                          
}TreeNode;
TreeNode *parse();
