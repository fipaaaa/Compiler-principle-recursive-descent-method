#include <stdio.h>
#include "dgxj.h"
#include <string.h>
#include <vector>
using namespace std;

static TreeNode * program(void); 
 
static TreeNode * programHead(void);

static TreeNode * declarePart(void);

static TreeNode * typeDec(void);

static TreeNode * typeDeclaration(void);

static TreeNode * typeDecList(void);

static TreeNode * typeDecMore(void);

static void  typeId(TreeNode * t);

static void  typeDef(TreeNode * t);

static void  baseType(TreeNode * t);

static void  structureType(TreeNode * t);

static void  arrayType(TreeNode * t);

static void  recType(TreeNode * t);

static TreeNode * fieldDecList(void);
 
static TreeNode * fieldDecMore(void);

static void  idList(TreeNode * t);

static void  idMore(TreeNode * t);
//变量声明
static TreeNode * varDec(void);

static TreeNode * varDeclaration(void);

static TreeNode * varDecList(void);

static TreeNode * varDecMore(void);

static void  varIdList(TreeNode * t);

static void  varIdMore(TreeNode * t);

static TreeNode * procDec(void);

static TreeNode * procDeclaration(void);

static void  paramList(TreeNode * t);

static TreeNode * paramDecList(void);

static TreeNode * param(void);

static TreeNode * paramMore(void);

static void  formList(TreeNode * t);

static void  fidMore(TreeNode * t);

static TreeNode * procDecPart(void);

static TreeNode * procBody(void);

static TreeNode * programBody(void);

static TreeNode * stmList(void);

static TreeNode * stmMore(void);

static TreeNode * stm(void);

static TreeNode * assCall(void);

static TreeNode * assignmentRest(void);	

static TreeNode * conditionalStm(void);

static TreeNode * loopStm(void);

static TreeNode * inputStm(void);		

static TreeNode * outputStm(void);	

static TreeNode * returnStm(void);

static TreeNode * callStmRest(void);

static TreeNode * actParamList(void);

static TreeNode * actParamMore(void);

static TreeNode * exp(void);	//处理表达式函数 

static TreeNode * simple_exp(void);	// 处理简单表达式函数

static TreeNode * term(void);//处理项函数

static TreeNode * factor(void);	//处理因子函数

static TreeNode * variable(void);

static void variMore(TreeNode * t);

static TreeNode * fieldvar(void);

static void fieldvarMore(TreeNode * t );
//打印部分
static void treePrint(TreeNode *t);

static void headPrint(TreeNode *t);

static void typePrint(TreeNode * t,int k);//类型声明输出

static void varPrint(TreeNode *t,int k);

static void varDecPrint(TreeNode *t,int k);

static void procPrint(TreeNode *t,int k);

static void procDecPrint(TreeNode *t,int k);

static void BodyPrint(TreeNode *t,int k);

static void BodySubPrint(TreeNode *t,int k);

static void  printzs(TreeNode  *tree);

TreeNode* getTreeNode(NodeKind n);

void read_next();

string temp_char;
extern vector<Token> v;
static Token nexttoken;

TreeNode* parse()
{
	TreeNode* tree = NULL;
	read_next();
	tree = program();
	return tree;
}

int number = 0;
void read_next()
{
	if (number < v.size()) {
		nexttoken = v[number];
		number++;
	}
}

void match(TokenType type)
{
	if (nexttoken.type == type)
		read_next();
	else
	{
		cout << "第" << nexttoken.line << "行匹配出错!";
		exit(0);
	}
}

TreeNode* program()
{
	TreeNode* tree = getTreeNode(ProK);//建立根结点
	tree->child[0] = programHead();
	tree->child[1] = declarePart();
	tree->child[2] = programBody();
	treePrint(tree);
	match(DOT);
	return tree;
}

TreeNode* getTreeNode(NodeKind n)
{
	TreeNode* t = new TreeNode();
	t->child[0] = NULL;
	t->child[1] = NULL;
	t->child[2] = NULL;
	t->idnum = 0;
	t->sibling = NULL;
	t->nodekind = n;
	t->lineno = nexttoken.line;
	return t;
}


TreeNode * programHead(void)
{
	TreeNode *t=getTreeNode(PheadK);
    match(PROGRAM);
	if(nexttoken.type==ID)
		t->name[t->idnum++]=nexttoken.context;//函数名
	match(ID);
	return t;
}

TreeNode* declarePart(void)  //声明调用
{
	if (nexttoken.type == TYPE)
		return typeDec();
	else if (nexttoken.type == VAR)
		return varDec();
	else if (nexttoken.type == PROCEDURE)
		return procDec();
	else return NULL;
}

TreeNode* programBody()
{
	TreeNode* t = getTreeNode(StmLK);
	match(BEGINl);
	if (t != NULL)
		t->child[0] = stmList();
	match(ENDl);
	return t;
}

void treePrint(TreeNode* t) {
	cout << "第" << t->lineno << "行 ProK" << endl;
	headPrint(t->child[0]);
	typePrint(t->child[1], 1);
	varPrint(t->child[1], 1);
	procPrint(t->child[1], 1);
	BodyPrint(t->child[2], 1);
}

void headPrint(TreeNode *t){
	cout <<"第"<< t->lineno<< "行     PheadK "<<t->name[0]<<endl;
}
//变量声明部分
TreeNode * varDec(void)
{
	TreeNode * t=getTreeNode(VarK);
	t->child[0]=varDeclaration();
    if(nexttoken.type==PROCEDURE)
		t->sibling=procDec();
	return t;
}
TreeNode * varDeclaration(void)
{
	match(VAR);
	TreeNode * t = varDecList();
    if(t==NULL)
		cout<<"需要变量声明!"<<endl;
	return t;
}
//
TreeNode * varDecList(void)
{
	TreeNode * t = getTreeNode(DecK);
	TreeNode * p = NULL;

	if ( t != NULL )
	{
		typeDef(t);
	    varIdList(t);
	    match(SEMI);
        p = varDecMore();
	    t->sibling = p;
	}
	return t;
}
//
void varIdList(TreeNode * t)
{
	if (nexttoken.type==ID)
	{
        t->name[(t->idnum)] =nexttoken.context;
        match(ID);
		t->idnum =(t->idnum ) + 1;
	}
	else 
	{
		cout<<"需要id!"<<endl;
		read_next();
	}
	varIdMore(t);
}
////////
void  varIdMore(TreeNode * t)
{
	switch(nexttoken.type)
	{
	case SEMI:
		     break;
	case COMMA:
		     match(COMMA);
			 varIdList(t);
			 break;
	default:
		cout<<"行数"<<nexttoken.line<< "找不到单词" << endl;
		read_next();
		break;
	}	
}
TreeNode * varDecMore(void)
{
	TreeNode *t=NULL;
	switch(nexttoken.type)
	{
	case PROCEDURE:
	case BEGINl:
		    break;
	case INTEGER:
	case CHARl:
	case ARRAY:
	case RECORD:
	case ID:
		t = varDecList();
		break;
	default:
		cout << "行数" << nexttoken.line << "找不到单词" << endl;
		read_next();
		break;
	}
	return t;
}

void varPrint(TreeNode * t,int k){
	int i;
	while(t!=NULL&&t->nodekind!=VarK)
		t=t->sibling;
	if(t!=NULL){
		cout << "第" << t->lineno << "行 " ;
		for(i=0;i<k;i++)
			cout<<"    ";
		cout<<"VarK"<<endl;
		k++;
		varDecPrint(t,k);
	}
}
void varDecPrint(TreeNode *t,int k){
	int i;
	t=t->child[0];
	while(t!=NULL){
		cout << "第" << t->lineno << "行 ";
		for(i=0;i<k;i++)
			cout << "    ";
		if(t->nodekind==DecK){
			switch(t->kind.dec){
			case ArrayK: 
				cout << "DecK " << "ArrayK " << t->attr.ArrayAttr.low << " " << t->attr.ArrayAttr.up <<" ";
				if (t->attr.ArrayAttr.childtype == IntegerK) {
					cout<<"IntegerK ";
				}
				else { 
					cout<<"CharK ";
				}
				for (i = 0; i < t->idnum; i++) {
					cout << t->name[i] << (char)32<<endl;
					
				}
				break;
			case CharK:  
				cout << "DecK " << "CharK ";
				for (i = 0; i < t->idnum; i++) {
					cout << t->name[i] << (char)32 ;
					
				}
				cout << endl;
				break;
			case IntegerK: 
				cout << "DecK " << "IntegerK ";
				for (i = 0; i < t->idnum; i++) {
					cout << t->name[i] << (char)32 ;
					
				}
				cout << endl;
				break;
			case RecordK: 
				cout << "DecK " << "RecordK " << t->name[0] << endl;
				break;
			case IdK: 
				cout << "DecK " << "IdK " << t->attr.type_name << " " << t->name[0] << endl;
				break;
			}
			varPrint(t,k+1);
			t=t->sibling;
		}
		else
			cout<<"error";
	}
}



TreeNode * typeDec(void){
		match(TYPE);
		return typeDeclaration();
}
TreeNode * typeDeclaration(void){                  //因为前面已经判断了TYPE，此处不再判断。
	TreeNode *t=getTreeNode(TypeK);
	t->child[0]=typeDecList();
	if(nexttoken.type==VAR)
		t->sibling=varDec();
	else if(nexttoken.type==PROCEDURE)
		t->sibling=procDec();
	return t;
}
TreeNode * typeDecList(void){		
	TreeNode *t=getTreeNode(DecK);
	typeId(t);match(EQ);typeDef(t);match(SEMI);
	t->sibling=typeDecMore();
	return t;
}
TreeNode * typeDecMore(void){
	if(nexttoken.type==ID)
		return typeDecList();
	else
		return NULL;
}
void  typeId(TreeNode * t){                   //认为不存在多个变量
	t->name[0]=nexttoken.context;
	match(ID);
	t->idnum=1;
}
void  typeDef(TreeNode * t){
	if(nexttoken.type==INTEGER||nexttoken.type==CHARl)
		baseType(t);
	else if(nexttoken.type==ARRAY||nexttoken.type==RECORD)
		structureType(t);
	else if(nexttoken.type==ID){
		t->kind.dec=IdK;
		strcpy(t->attr.type_name,nexttoken.context.c_str());
		match(ID);
	}
	else{
		cout<<"第"<< nexttoken.line<<"行没有匹配成功";
		exit(0);
	}	
}
void  baseType(TreeNode * t){
	if(nexttoken.type==INTEGER){
		t->kind.dec=IntegerK;
		match(INTEGER);
	}
	else{
		t->kind.dec=CharK;
		match(CHARl);
	}
}
void  structureType(TreeNode * t){
	if(nexttoken.type==ARRAY){
		arrayType(t);
	}
	else{
		t->kind.dec=RecordK;
		recType(t);
	}
}
void  arrayType(TreeNode * t){
	t->kind.dec=ArrayK;
	match(ARRAY);
	match(LMIDPAREN);
	if(nexttoken.type==INTC)
		t->attr.ArrayAttr.low=atoi(nexttoken.context.c_str());
	match(INTC);
	match(UNDERANGE);
	if(nexttoken.type==INTC)
		t->attr.ArrayAttr.up=atoi(nexttoken.context.c_str());
	match(INTC);
	match(RMIDPAREN);
	match(OF);
	if(nexttoken.type==INTEGER){
		t->attr.ArrayAttr.childtype=IntegerK;
		read_next();
	}
	else if(nexttoken.type==CHARl){
		t->attr.ArrayAttr.childtype=CharK;
		read_next();
	}
}
void  recType(TreeNode * t){
	match(RECORD);
	t->child[0]=fieldDecList();
	match(ENDl);
}
TreeNode * fieldDecList(void){
	TreeNode *t=getTreeNode(DecK);
	if(nexttoken.type==INTEGER||nexttoken.type==CHARl){
		baseType(t);
		idList(t);
		t->sibling=fieldDecMore();
	}
	else if(nexttoken.type==ARRAY){
		arrayType(t);
		idList(t);
		t->sibling=fieldDecMore();
	}
	else{
		cout << "第" << nexttoken.line << "行没有匹配成功";
		exit(0);
	}
	return t;
}
TreeNode * fieldDecMore(void){
	if(nexttoken.type==INTEGER||nexttoken.type==CHARl||nexttoken.type==ARRAY)
		return fieldDecList();
	else
		return NULL;
}
void  idList(TreeNode * t){
	if(nexttoken.type==ID){
		t->name[t->idnum]=nexttoken.context;
		match(ID);
		t->idnum++;
		idMore(t);
	}
}
void  idMore(TreeNode * t){
	if(nexttoken.type==COMMA){
		match(COMMA);
		idList(t);
	}
	else match(SEMI);
}
void typePrint(TreeNode * t,int k){
	int i;
	if(t->nodekind==TypeK){
		cout << "第" << t->lineno << "行 ";
		for(i=0;i<k;i++)
			cout << "    ";
		cout << "TypeK" << endl;
		//printf("%s\n","TypeK");
		k++;
	}
	t=t->child[0];
	while(t!=NULL){
		cout << "第" << t->lineno << "行 ";
		for(i=0;i<k;i++)
			cout<<"    ";
		if(t->nodekind==DecK){
			switch(t->kind.dec){
			case ArrayK: 
				       cout << "DecK " << "ArrayK " << t->attr.ArrayAttr.low << " " << t->attr.ArrayAttr.up<<" ";
					   if (t->attr.ArrayAttr.childtype == IntegerK) {
						   cout<<"IntegerK ";
					   }
					   else {
						   cout<<"CharK ";
					   }
					   for (i = 0; i < t->idnum; i++) {
						   cout << t->name[i] << (char)32 ;
					   }
					   cout << endl;
					   break;
			case CharK:  
				cout << "DecK " << "CharK ";
				for (i = 0; i < t->idnum; i++) {
					cout << t->name[i] << (char)32 ;
				}
				cout << endl;
				break;
			case IntegerK: 
				cout << "DecK " << "IntegerK ";
				for (i = 0; i < t->idnum; i++) {
					cout << t->name[i] << (char)32;			
				}
				cout << endl;
				break;
			case RecordK: 
				cout << "DecK " << "RecordK " << t->name[0] << endl;
				break;
			case IdK: 
				cout << "DecK " << "IdK " << t->attr.type_name << " " << t->name[0] << endl;
				break;
			}
			typePrint(t,k+1);
			t=t->sibling;
		}
		else
			cout << "error";
	}
}



//过程声明部分

TreeNode * procDec(void){
	TreeNode *t=getTreeNode(ProcK);
	t->child[0]=procDeclaration();
	return t;
}
TreeNode * procDeclaration(void){
	match(PROCEDURE);
	TreeNode *t=getTreeNode(ProcDecK);
	if(nexttoken.type==ID){
		t->name[0]=nexttoken.context;
		t->idnum++;
		match(ID);
		match(LPAREN);
		paramList(t);
		match(RPAREN);
		match(SEMI);
		t->child[1]=procDecPart();
		t->child[2]=procBody();
	}
	else{
		cout << "第" << nexttoken.line << "行没有匹配成功";
		exit(0);
	}
	if(nexttoken.type==PROCEDURE)
		t->sibling=procDeclaration();
	return t;
}
void  paramList(TreeNode * t){
	if(nexttoken.type!=RPAREN)
		t->child[0]=paramDecList();
}
TreeNode * paramDecList(void){
	TreeNode *t=param();
	TreeNode *p=paramMore();
	t->sibling=p;
	return t;
}
TreeNode * param(void){
	TreeNode *t=getTreeNode(DecK);
	if(nexttoken.type==VAR){
		t->attr.ProcAttr.paramt=varparamType;
		match(VAR);
	}
	else 
		t->attr.ProcAttr.paramt=valparamType;
	typeDef(t);
	formList(t);
	return t;
}
TreeNode * paramMore(void){
	if(nexttoken.type==SEMI){
		match(SEMI);
		return paramDecList();
	}
	else return NULL;
}
void  formList(TreeNode * t){
	if(nexttoken.type==ID){
		t->name[t->idnum++]=nexttoken.context;
		match(ID);
	}
	fidMore(t);
}
void  fidMore(TreeNode * t){
	if(nexttoken.type==COMMA){
		match(COMMA);
		formList(t);
	}
}
TreeNode * procDecPart(void)
{
	 return declarePart();
}
TreeNode * procBody(void)
{
	TreeNode *t=programBody();
	if (t == NULL) {
		cout <<"第"<< nexttoken.line << "需要程序中间部分";
	}
	return t;
}

TreeNode *stmList()
{
	TreeNode * t = stm();
    TreeNode * p = stmMore();
	t->sibling = p;
	return t;
}
TreeNode * stmMore(void){
	if(nexttoken.type==SEMI){
		match(SEMI);
		return stmList();
	}
	else return NULL;
}
TreeNode * stm(void){
	switch(nexttoken.type){
	case IF:return conditionalStm();
	case WHILE:return loopStm();
	case READ:return inputStm();
	case WRITE:return outputStm();
	case RETURNl:return returnStm();
	case ID:temp_char=nexttoken.context;match(ID);return assCall();
	default:
		cout << "第" << nexttoken.line << "行没有匹配成功"; 
		exit(0);
	}
}
TreeNode * assCall(void){
	if(nexttoken.type==ASSIGN||nexttoken.type==LMIDPAREN||nexttoken.type==DOT){
		return assignmentRest();
	}
	else if(nexttoken.type==LPAREN)
		return callStmRest();
	else{
		cout << "第" << nexttoken.line << "行没有匹配成功";
		exit(0);
	}
}
TreeNode * assignmentRest(void){
	TreeNode *t=getTreeNode(StmtK);
	t->kind.stmt=AssignK;
	TreeNode *p=getTreeNode(ExpK);
	t->child[0]=p;
	p->name[p->idnum++]=temp_char;
	p->kind.exp=VariK;
	p->attr.ExpAttr.varkind=IdV;
	variMore(p);
	match(ASSIGN);
	t->child[1]=exp();
	return t;
}
TreeNode * conditionalStm(void){
	TreeNode *t=getTreeNode(StmtK);
	t->kind.stmt=IfK;
	match(IF);
	t->child[0]=exp();
	match(THEN);
	t->child[1]=stmList();
	match(ELSE);
	t->child[2]=stmList();
	match(FI);
	return t;
}
TreeNode * loopStm(void){
	TreeNode *t=getTreeNode(StmtK);
	t->kind.stmt=WhileK;
	match(WHILE);
	t->child[0]=exp();
	match(DO);
	t->child[1]=stmList();
	match(ENDWH);
	return t;
}
TreeNode * inputStm(void){
	TreeNode *t=getTreeNode(StmtK);
	t->kind.stmt=ReadK;
	match(READ);
	match(LPAREN);
	typeId(t);
	match(RPAREN);
	return t;
}
TreeNode * outputStm(void){
	TreeNode *t=getTreeNode(StmtK);
	t->kind.stmt=WriteK;
	match(WRITE);
	match(LPAREN);
	t->child[0]=exp();
	match(RPAREN);
	return t;
}
TreeNode * returnStm(void){
	TreeNode *t=getTreeNode(StmtK);
	t->kind.stmt=ReturnK;
	match(RETURNl);
	return t;
}
TreeNode * callStmRest(void){
	TreeNode *t=getTreeNode(StmtK);
	t->kind.stmt=CallK;
	TreeNode *p=getTreeNode(ExpK);
	t->child[0]=p;
    p->name[p->idnum++]=temp_char;
	p->kind.exp=VariK;
	p->attr.ExpAttr.varkind=IdV;
	match(LPAREN);
	t->child[1]=actParamList();
	match(RPAREN);
	return t;
}
TreeNode * actParamList(void){
	if(nexttoken.type==RPAREN)
		return NULL;
	else if(nexttoken.type==ID||nexttoken.type==INTC){
		TreeNode * t=exp();
		t->sibling=actParamMore();
		return t;
	}
	else{
		cout << "第" << nexttoken.line << "行没有匹配成功";
		exit(0);
	}
}
TreeNode * actParamMore(void){
	if(nexttoken.type==RPAREN)
		return NULL;
	else if(nexttoken.type==COMMA){
		match(COMMA);
		return actParamList();
		
	}
	else{
		cout << "第" << nexttoken.line << "行没有匹配成功";
		exit(0);
	}
}
//表达式递归处理分析程序
TreeNode * exp(void)
{
  TreeNode * t = simple_exp();
  if ((nexttoken.type==LT)||(nexttoken.type==EQ)) //该节点有两个子节点，分别表示运算符的左面和右面
  {
    TreeNode * p = getTreeNode(ExpK);
    p->kind.exp=OpK;
	/* 新语法树节点p创建成功,初始化p第一个子节点成员child[0]
	 * 并将当前单词token(为EQ或者LT)赋给语法树节点p的运算符成员attr.op*/
    if (p!=NULL) 
	{
	  p->child[0] = t;
      p->attr.ExpAttr.op = nexttoken.type;

	  /* 将新的表达式类型语法树节点p作为函数返回值t */
      t = p;
    }

	/* 当前单词token与指定逻辑运算符单词(为EQ或者LT)匹配 */
    match(nexttoken.type);

	/* 语法树节点t非空,调用简单表达式处理函数simple_exp()	*
	 * 函数返回语法树节点指针给t的第二子节点成员child[1]	*/
    if (t!=NULL)
      t->child[1] = simple_exp();
  }
  return t;
}
TreeNode * simple_exp(void)
{
  /* 调用元处理函数term(),函数返回语法树节点指针给t */
  TreeNode * t = term();

  /* 当前单词token为加法运算符单词PLUS或MINUS */
  while ((nexttoken.type==PLUS)||(nexttoken.type==MINUS))

  {
    /* 创建新OpK表达式类型语法树节点，新语法树节点指针赋给p */
	TreeNode * p = getTreeNode(ExpK);
    p->kind.exp=OpK;

 	/* 语法树节点p创建成功,初始化p第一子节点成员child[0]	*
	 * 返回语法树节点指针给p的运算符成员attr.op				*/
    if (p!=NULL) 
	{
      p->lineno = nexttoken.line;
	  p->child[0] = t;
      p->attr.ExpAttr.op = nexttoken.type;

	  /* 将函数返回值t赋成语法树节点p */
      t = p;

	  /* 当前单词token与指定加法运算单词(为PLUS或MINUS)匹配 */
      match(nexttoken.type);

	  /* 调用元处理函数term(),函数返回语法树节点指针给t的第二子节点成员child[1] */
      t->child[1] = term();
    }
  }
  return t;
}
//////////////
TreeNode * term(void)
{
  TreeNode * t = factor();
  /* 当前单词token为乘法运算符单词TIMES或OVER */
  while ((nexttoken.type==TIMES)||(nexttoken.type==OVER))

  {
	TreeNode * p = getTreeNode(ExpK);
    p->kind.exp=OpK;
    if (p!=NULL) 
	{
	  p->child[0] = t;
      p->attr.ExpAttr.op = nexttoken.type;
      t = p;
	}
    match(nexttoken.type);
    p->child[1] = factor();
    
  }
  return t;
}
/////////////////////////////
TreeNode * factor(void)
{
  
  TreeNode * t = getTreeNode(ExpK);
  switch (nexttoken.type) 
  {
    case INTC :									
	  /* 创建新的ConstK表达式类型语法树节点,赋值给t */
     t->kind.exp=ConstK;
		  t->attr.ExpAttr.val = atoi(nexttoken.context.c_str());
		  t->attr.ExpAttr.varkind=IdV;
     match(INTC);
     break;
    case ID :
	  /* 创建新的IdK表达式类型语法树节点t */	  
	  t = variable();
      break;

	/* 当前单词token为左括号单词LPAREN */
    case LPAREN :		

	  /* 当前单词token与左括号单词LPAREN匹配 */
      match(LPAREN);					

	  /* 调用表达式处理函数exp(),函数返回语法树节点指针给t */
      t = exp();

	  /* 当前单词token与右括号单词RPAREN匹配 */
      match(RPAREN);					

      break;

	/* 当前单词token为其它单词 */
    default:
		cout << "行数" << nexttoken.line << "找不到单词" << endl;
      read_next();
	  
	  break;
    }
  /* 函数返回表达式类型语法树节点t */
  return t;
}
//////////////
TreeNode * variable(void)
{
	TreeNode * t = getTreeNode(ExpK);
    t->kind.exp=VariK;
	if ((t!=NULL) && (nexttoken.type==ID))
	{
		t->name[0] =nexttoken.context;
		t->attr.ExpAttr.varkind=IdV;
        (t->idnum)++;
	}
	
	match(ID);
	variMore(t);
	return t;
}
	
void variMore(TreeNode * t)
{
	switch(nexttoken.type)
	{	
	case ASSIGN:
	case TIMES:
	case EQ:
	case LT:
	case PLUS:
	case MINUS:
	case OVER:
	case RPAREN:
	case RMIDPAREN:
	case SEMI:
	case COMMA:
	case THEN:
	case ELSE:
	case FI:
	case DO:
	case ENDWH:
	case ENDl:
		break;
	case LMIDPAREN:
		match(LMIDPAREN);
		
		/*用来以后求出其表达式的值，送入用于数组下标计算*/
		t->child[0] = exp();

		t->attr.ExpAttr.varkind = ArrayMembV;

		/*此表达式为数组成员变量类型*/
		t->child[0]->attr.ExpAttr.varkind = IdV;
		match(RMIDPAREN);
		break;
	case DOT:
		match(DOT);
		/*第一个儿子指向域成员变量结点*/
		t->child[0] = fieldvar();

		t->attr.ExpAttr.varkind = FieldMembV;

		t->child[0]->attr.ExpAttr.varkind = IdV;
		break;
	default:
		cout << "行数" << nexttoken.line << "找不到单词" << endl;
		read_next();
		break;
	}
}
/////////////////////////
TreeNode * fieldvar(void)
{
    TreeNode * t = getTreeNode(ExpK);
    t->kind.exp=VariK;
	if ((t!=NULL) && (nexttoken.type==ID))
	  {
		  t->lineno = nexttoken.line;
		  t->name[0] =nexttoken.context;
          (t->idnum)++;
	  }	
	match(ID);
	
	fieldvarMore(t);

	return t;
}

//////////////////////
void fieldvarMore(TreeNode * t )
{
	switch(nexttoken.type)
	{
	case ASSIGN:
	case TIMES:
	case EQ:
	case LT:
	case PLUS:
	case MINUS:
	case OVER:
	case RPAREN:
	case SEMI:
	case COMMA:
	case THEN:
	case ELSE:
	case FI:
	case DO:
	case ENDWH:
	case ENDl:
		break;
	case LMIDPAREN:
		match(LMIDPAREN);
		
		/*用来以后求出其表达式的值，送入用于数组下标计算*/
		t->child[0] = exp();
		t->child[0]->attr.ExpAttr.varkind = ArrayMembV;
		match(RMIDPAREN);
		break;
	default:
		cout << "行数" << nexttoken.line << "找不到单词" << endl;
		read_next();
		break;
	}
}
void procPrint(TreeNode *t,int k){
	int i;
	TreeNode *p;
	while(t->sibling!=NULL)
		t=t->sibling;
	if(t->nodekind==ProcK){
		cout << "第" << t->lineno << "行 ";
		for (i = 0; i < k; i++) {
			cout << "    ";
		}
		cout << "ProcK" << endl;
		k++;
		t=t->child[0];
		while(t!=NULL&&t->nodekind==ProcDecK){
			cout << "第" << t->lineno << "行 ";
			for(i=0;i<k;i++)
				printf("    ");
			k++;
			cout << "ProcDecK " << t->name[0] << endl;
			for(i=0;i<3;i++){
				p=t->child[i];
				procDecPrint(p,k);
			}
			t=t->sibling;
		}
	}
}
void procDecPrint(TreeNode *t,int k){
	if(t!=NULL){
		while(t!=NULL&&t->nodekind==DecK){
			cout << "第" << t->lineno << "行 ";
			for(int i=0;i<k;i++)
				cout << "    ";
			if (t->attr.ProcAttr.paramt == valparamType) {
				cout << "DecK value param: ";
			}
			else {
				cout << "DecK var param: ";
			}
			switch(t->kind.dec){
			case ArrayK: 
				         cout << "ArrayK " << t->attr.ArrayAttr.low << " " << t->attr.ArrayAttr.up << " "; 
						 if (t->attr.ArrayAttr.childtype == IntegerK) {
							 cout << "IntegerK ";
						 }
						 else { 
							 cout << "CharK ";
						 }
						 for (int i = 0; i < t->idnum; i++) {
							 cout << t->name[i] << (char)32 ;
							 
						 }
						 cout << endl;
						 break;
			case CharK: 
				cout << "CharK ";
				for (int i = 0; i < t->idnum; i++) {
					cout << t->name[i] << (char)32 ;
					
				}
				cout << endl;
				break;
			case IntegerK: 
				cout << "IntegerK ";
				for (int i = 0; i < t->idnum; i++) {
					cout << t->name[i] << (char)32 ;
					
				}
				cout << endl;
				break;
			case RecordK:
				cout << "RecordK " << t->name[0] << endl;
				break;
			case IdK: 
				cout << "IdK " << t->attr.type_name << " " << t->name[0] << endl;
				break;
			}
			t=t->sibling;
		}
		if(t!=NULL&&(t->nodekind==TypeK||t->nodekind==VarK||t->nodekind==ProcK)){
			if(t->nodekind==TypeK){
				typePrint(t,k-1);
				t=t->sibling;
			}
			if(t!=NULL&&t->nodekind==VarK){
				varPrint(t,k-1);
				t=t->sibling;
			}
			if(t!=NULL&&t->nodekind==ProcK){
				procPrint(t,k-1);
				t=NULL;
			}
		}
		if(t!=NULL){
			BodyPrint(t,k-1);
		}
	}
}
void BodyPrint(TreeNode *t,int k){
	if(t!=NULL){
		cout << "第" << t->lineno << "行 ";
		for(int i=0;i<k;i++)
			cout << "    ";
		cout << "StmLK" << endl;
		k++;
		t=t->child[0];
		BodySubPrint(t,k);
	}
}
void BodySubPrint(TreeNode *t,int k){
	int i;
	while(t!=NULL){
		cout << "第" << t->lineno << "行 ";
		for(i=0;i<k;i++)
			cout << "    ";
		if(t->nodekind==StmtK){
			cout << "Stmtk ";
			switch(t->kind.stmt){
			case IfK:
				cout<<"If" << endl;
				break;
			case WhileK:
				cout<< "While" << endl;
				break;
			case AssignK:
				cout<< "Assign" <<endl;
				break;
			case ReadK:
				cout<<"Read "<< t->name[0] <<endl;
				break;
			case WriteK:
				cout<<"Write" <<endl;
				break;
			case CallK:
				cout<<"Call" <<endl;
				break;
			case ReturnK:
				cout<<"Return" <<endl;
				break;
			}
		}
		else{
			cout << "ExpK ";
			switch(t->kind.exp){
			case OpK:
				cout << "Op ";
			switch(t->attr.ExpAttr.op){
			case LT:printf("<\n");break;
			case EQ:printf("=\n");break;
			case PLUS:printf("+\n");break;
			case MINUS:printf("-\n");break;
			case TIMES:printf("*\n");break;
			case OVER:printf("/\n");break;}
			break;
			case ConstK:
				cout << "Const Id " << t->attr.ExpAttr.val << endl;
				break;
			case VariK:
				cout << "Vari ";
			switch(t->attr.ExpAttr.varkind){
			case IdV:printf("Id ");break;
			case ArrayMembV:printf("ArrayMember ");break;
			case FieldMembV:printf("FieldMember ");break;} 
			cout << t->name[0] << endl;
			break;
			}
		}
		for(i=0;i<3;i++)
			BodySubPrint(t->child[i],k+1);
		t=t->sibling;
	}
}

