#include "analyzer.h"
#include"Token.h"
#include <string>
#include <vector>
#include <fstream>
//定义节点类型
typedef enum {ProK,PheadK,TypeK,VarK,ProcDecK,StmLK,DecK,StmtK,ExpK,ProcK}
              NodeKind;
//类型声明节点的具体类型
typedef enum {ArrayK,CharK,IntegerK,RecordK,IdK}  DecKind;
// 变量类型VarKind类型的枚举定义:           
// 标识符IdV,数组成员ArrayMembV,域成员FieldMembV
typedef enum {IdV,ArrayMembV,FieldMembV} VarKind; 
//语句声明节点的类型
typedef enum {IfK,WhileK,AssignK,ReadK,WriteK,CallK,ReturnK} StmtKind;
// 表达式类型ExpKind类型的枚举定义:         
typedef enum {OpK,ConstK,VariK} ExpKind;

// 类型检查ExpType类型的枚举定义:
//空Void,整数类型Integer,字符类型Char     
typedef enum {Void,Integer,Boolean} ExpType;

// 参数类型ParamType类型的枚举定义：        
// 值参valparamType,变参varparamType        
typedef enum {valparamType,varparamType} ParamType;
//语法树节点 
typedef struct treeNode

   { 
	 struct treeNode * child[3];	//子节点指针				
     struct treeNode * sibling;	//兄弟节点指针
     int lineno;		//源代码行号
     NodeKind nodekind;	//节点类型
	 int idnum; //标识符个数
	 string name[20];//标识符名

     union 
	 {
		 DecKind  dec;
	     StmtKind stmt; 
		 ExpKind  exp; 
	 } kind;//具体类型

	 

	 struct 
	 {
		struct
			{	
				int low;              //数组下界
				int up;               // 数组上界
				DecKind   childtype;  // 数组的子类型
			}ArrayAttr;               //数组属性
	         
		struct
			{	
				ParamType  paramt;     //参数类型
			}ProcAttr;                 //过程属性 
		
		struct
			{
				TokenType op; //表达式的操作符						
				int val;		      //表达式的值
				VarKind  varkind;     // 变量的类别
				ExpType type;         // 用于类型检查
			}ExpAttr;	           //表达式属性 

      char type_name[10];        //类型名是标识符     
             
	 } attr;                          
}TreeNode;
TreeNode *parse();
