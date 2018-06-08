#pragma once


typedef enum{RB_RED,RB_BLACK}TREE_COLOR;
template<typename T>
struct  BinNode
{
	typedef BinNode<T>*         BinNodePtr;
	T data;
	BinNodePtr parent, lc, rc;
	int height;
	int npl;
	TREE_COLOR color;

	BinNode() : parent(NULL),lc(NULL),rc(NULL),height(0),npl(1),color(RB_RED){}
	BinNode(T e, BinNodePtr p = NULL, BinNodePtr lc = NULL, BinNodePtr rc = NULL, int h = 0, int l = 1, TREE_COLOR c = RB_RED) :data(e), parent(p), lc(lc), rc(rc), height(h), npl(l),color(c){}

	int Size()
	{
		return 0;
	}
	BinNodePtr insertAsLC(const T&)
	{
		return lc = new BinNode(e, this);
	}
	BinNodePtr insertAsRC(const T&)
	{
		return rc = new BinNode(e, this);
	}
	BinNodePtr succ()
	{
		return BinNodePtr();
	}

	template<typename VST>
	void travLevel(VST&) {}
	template<typename VST>
	void travPre(VST&) {}
	template<typename VST>
	void travIn(VST&) {}
	template<typename VST>
	void travPost(VST&) {}

	bool operator< (const BinNode& bn) { return data < bn->data; }
	bool operator== (const BinNode& bn) { return data == bn->data; }
};

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) ((x).parent)
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x) (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc:(x)->parent->parent->lc)
#define FromeParentTo(x) (IsRoot(x) ? _root : (IsLChild(x) ? (x)->parent->lc:(x)->parent->rc))
#define stature(p) ((p) ? (p)->height:-1)


template<typename T>
class BinTree
{
public:
	typedef typename BinTree<T>              _MyType;
	typedef typename BinTree<T>*             _MyTypePtr;
	typedef typename BinNode<T>              _NodeType;
	typedef typename BinNode<T>::BinNodePtr  _NodePtr;
private:
	int _size;
	_NodePtr _root;

	virtual int updateHeight(_NodePtr x)
	{
		while (x) {
			updateHeight(x);
			x = x->parent;
		}
	}

	void updateHeightAbove(_NodePtr x)
	{
		return x->height = 1 + max(stature(x->lc), stature(x->rc));
	}
public:
	BinTree() : _size(0), _root(NULL) {}
	~BinTree() {}


	int size() const { return _size; }
	bool empty() const 
	{
		return !_root;
	}

	_NodePtr root() const{
		return _root; 
	}
	_NodePtr insertAsRoot(const T& e){
		_size = 1;
		return _root = new _NodeType(e);
	}

	_NodePtr insertAsLC(_NodePtr x, const T& e)
	{
		_size++;
		x->insertAsLC(e);
		UpdateHegitAbove(x);
		return x->lc;
	}

	_NodePtr insertAsRC(_NodePtr x, const T& e)
	{
		_size++;
		x->insertAsRC(e);
		UpdateHegitAbove(x);
		return x->rc;
	}

	_NodePtr attachAsLC(_NodePtr x, _MyTypePtr& t)
	{
		if (x->lc = t.root()) x->lc->parent = x;
		_size += t->size();
		t->_root = NULL;t->_size = 0;delete t; t = NULL;
		return x;
	}

	_NodePtr attachAsRC(_NodePtr x, _MyTypePtr& t)
	{
		if (x->rc = t.root()) x->rc->parent = x;
		_size += t->size();
		t->_root = NULL;t->_size = 0;delete t; t = NULL;
		return x;
	}

	int remove(_NodePtr x)
	{
		FromeParentTo(*x) = NULL;
		updateHeightAbove(x->parent);
		int n = removeAt(x);_size -= n;
		return n;
	}
	_MyTypePtr secede(_NodePtr x)
	{
		FromeParentTo(*x) = NULL;
		updateHeightAbove(x->parent);
		_MyTypePtr S = new _MyType;
		S->_root = x;x->parent = NULL;
		S->_size = x->size();
		_size -= S->_size;
		return S;
	}

	template<typename T>
	static int removeAt(BinNode::BinNodePtr x)
	{
		if (!x) return 0;
		int n = 1 + removeAt(x->lc) + removeAt(x->rc);
		delete x->data;delete x;return n;
	}

	template<typename VST>
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }
	template<typename VST>
	void travPre(VST& visit) { if (_root) _root->travPre(visit); }
	template<typename VST>
	void travIn(VST& visit) { if (_root) _root->travIn(visit); }
	template<typename VST>
	void travPost(VST& visit) { if (_root) _root->travPost(visit); }

	bool operator< (const _MyType& other) { return _root && other.root() && _root < other.root(); }
	bool operator== (const _MyType& other) { return _root && other.root() && _root == other.root(); }
};
