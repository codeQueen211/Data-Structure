// //
// // Created by Weaam on 10/01/2020.
// //

// #ifndef HW2DATASTRUCTURE_UNIONFIND_H
// #define HW2DATASTRUCTURE_UNIONFIND_H
// #include <iostream>
// // #include "Exception.h"
// // #include "dataCenter.h"
// using namespace std;
// using namespace UnionFindExceptions;

// //template <typename Group>
// class UnionFind {
//     int n;
//     int* size;
//     int* parent;
//     int* name;
//     int* root;
//     dataCenter** info;
// public:
//     explicit UnionFind(int n) : n(n), size(), parent(), name() , info() {
//         /*if(n<2) {
//             throw InvalidInput();
//         }*/
//         try {
//             size = new int[n+1];
//             parent = new int[n+1];
//             name = new int[n+1];
//             root = new int[n+1];
//             info = new dataCenter*[n+1];
//         } catch (std::bad_alloc& e) {
//             throw AllocationError();
//         }
//         for(int i=0; i<n+1; i++) {
//             size[i] = 1;
//         }
//         for(int i=0; i<n+1; i++) {
//             parent[i] = -1;
//         }
//         for(int i=0; i<n+1; i++) {
//             name[i] = i;
//         }
//         for(int i=0; i<n+1; i++) {
//             root[i] = i;
//         }
//         for(int i=0; i<n+1; i++) {
//             info[i] = new dataCenter(i);
//         }
//     }

//     ~UnionFind() {
//         delete[] size;
//         delete[] parent;
//         delete[] name;
//         delete[] root;
//         for(int i=0; i<n+1; i++) {
//             if(info[i]){
//                 delete info[i];
//             }
//         }
//         delete[] info;
//     }

//     /**
//      * 	Get the Group with the name i.
//      *
//      *	@return:
//      *	- pointer to the Group with the name i
//      *
//      *	@exceptions:
//      *	- InvalidInput if i is not in the range [0, n-1]
//      *	- GroupNotFound if the group i doesn't exist
//      */
//      int* getSizeArr(){
//          return size;
//      }
//     dataCenter* get(int i) {
//         if(i<1 || i>n) {
//             throw InvalidInput();
//         }
//       /*  if(root[i]==-1) {
//             throw GroupNotFound();
//         }*/
//         return info[i];
//     }

//     /**
//      * 	Finds the name of the group that contains i.
//      *
//      * 	Note: updates the route from i to the head to short the route in later
//      * 			uses of the function Find
//      * 	@return:
//      * 	- the name of the group that contains i
//      *
//      * 	@exceptions:
//      * 	- InvalidInput if i is not in the range [0, n-1]
//      */
//     int find(int i) {
//         if(i<1 || i>n) {
//             throw InvalidInput();
//         }
//         int head = i;
//         while(parent[head]!=-1) {
//             head = parent[head];
//         }

//         int node = i, temp;
//         while(parent[node]!=-1 && parent[node]!=head) {
//             temp = node;
//             node = parent[node];
//             parent[temp] = head;
//         }

//         return name[head];
//     }

//     /**
//      *	Connects the group p and the group q into one big group.
//      *
//      *	@return:
//      *	- the name of the new group
//      *
//      *	@exceptions:
//      *	- InvalidInput if p or q is not in the range [0, n-1] or the groups
//      *		don't exist
//      *	- SameGroup if q and q are the same group
//      */
//     int unite(int p, int q) {
//         if(p<0 || p>n || q<0 || q>n) {
//             throw InvalidInput();
//         }
//         if(p == q ) {
//             return p;
//         }
//         if(root[p] == -1 && root[q] == -1 && parent[p] != -1 && parent[q] != -1 ){
//             return unite(parent[p],parent[q]);
//         }
//         if(root[p]==-1&&name[p]!=-1){
//             int pw = name[p];
//             if(size[find(pw)]== 0){
//                 root[find(pw)]=-1;
//                 parent[find(pw)]=q;
//                 name[find(pw)]=q;
//                 return q;
//             }
//             //return p;
//         }
//         if(root[q]==-1 && name[q]!=-1){
//             int qw = name[q];
//             if(size[find(qw)]==0){
//                 root[find(qw)] = -1;
//                 parent[find(qw)] = p;
//                 name[find(qw)] = p;
//                 return p;
//             }
//         }
//         if(name[p]!=-1) p=find(name[p]);
//         if(name[q]!=-1) q=find(name[q]);
//         if((info[p]->getRankedTree()->Getsize()==0)&&(info[q]->getRankedTree()->Getsize()==0)) {
//             if(p>q) {
//                 size[p] = 0;
//                 root[q] = -1;
//                 root[p] = p;
//                 parent[q] = p;
//                 name[q] = p;
//                 return p;
//             }
//             else {
//                 size[q]=0;
//                 root[p]=-1;
//                 root[q]=q;
//                 parent[p] = q;
//                 name[p] = q;
//                 return q;
//             }
//         }
//         if(info[p]->getRankedTree()->Getsize()==0){
//             root[q] = q;
//             root[p] = -1;
//             parent[p] = q;
//             name[p] = q;
//             return q;
//         }
//         if(info[q]->getRankedTree()->Getsize()==0){
//             root[q] = -1;
//             root[p] = p;
//             parent[q] = p;
//             name[q] = p;
//             return p;
//         }
//         int bigger = (size[root[p]]>size[root[q]]) ? p : q ;
//         int smaller = (size[root[p]]>size[root[q]]) ? q : p ;
//         size[root[bigger]]+=size[root[smaller]];
//         parent[root[smaller]]=root[bigger];

//         name[root[bigger]] = p;
//         name[root[smaller]] = -1;
//         root[p] = root[bigger];
//         root[q] = -1;
//         //info[p]->updateStrongest(info[q]->getStrongestTrollID(),info[q]->getStrongestTrollStrength());
//         info[p]->getRankedTree()->mergeAvlTrees(info[q]->getRankedTree());
//         //delete info[q];
//      // dataCenter* temp=  info[q]  ;
//      // info[q]=NULL;
//      // delete temp;


//         return p;
//     }

//     void print() {
//         cout << "new:--------------------------------------------" << endl;
//         for(int i=0; i<n; i++) {
//             cout << "key: " << i << ",		group: " << find(i) << endl;
//         }
//         cout << "by group:" << endl;
//         for(int i=0; i<n; i++) {
//             cout << "group "<< i <<"| root: " << root[i] << "	ptr: " << info[i] << endl;
//         }
//     }

// };

// #endif //HW2DATASTRUCTURE_UNIONFIND_H

#ifndef HW2DATASTRUCTURE_UNIONFIND_H
#define HW2DATASTRUCTURE_UNIONFIND_H

#include <iostream>
#include "Records.h"

using namespace std;
class UnionFind {
    int n; //number of r_id in the ds
    int* size;
    int* parent;
    int* name;
    int* root;
    Records** info;

public:
    UnionFind() = default;
    explicit UnionFind(int n)
        : n(n), size(), parent(), name(), info()
    {
        size = new int[n + 1];
        parent = new int[n + 1];
        name = new int[n + 1];
        root = new int[n + 1];
        info = new Records*[n + 1];
        for (int i = 0; i < n + 1; i++) {
            size[i] = 1;
        }
        for (int i = 0; i < n + 1; i++) {
            parent[i] = -1;
        }
        for (int i = 0; i < n + 1; i++) {
            name[i] = i;
        }
        for (int i = 0; i < n + 1; i++) {
            root[i] = i;
        }
        for (int i = 0; i < n + 1; i++) {
            info[i] = new Records(i, 0, 0);
        }
    }

    ~UnionFind()
    {
        delete[] size;
        delete[] parent;
        delete[] name;
        delete[] root;
        for (int i = 0; i < n + 1; i++) {
            if (info[i]) {
                delete info[i];
            }
        }
        delete[] info;
    }

    int* getSizeArr() {
        return size;
    }

    Records* get(int i)
    {
        if (i < 1 || i > n) {
            return nullptr;
        }
        return info[i];
    }

    int find(int i) //r_id
    {
        if (i < 1 || i > n) {
            return -1;
        }
        int head = i;
        while (parent[head] != -1) {
            head = parent[head];
        }

        int node = i, temp;
        while (parent[node] != -1 && parent[node] != head) {
            temp = node;
            node = parent[node];
            parent[temp] = head;
        }

        return name[head];
    }

    int unite(int p, int q)
    {
        if (p < 0 || p > n || q < 0 || q > n) {
            return -1;
        }
        if (p == q) {
            return p;
        }
        if (root[p] == -1 && root[q] == -1 && parent[p] != -1 && parent[q] != -1) {
            return unite(parent[p], parent[q]);
        }
        if (root[p] == -1 && name[p] != -1) {
            int pw = name[p];
            if (size[find(pw)] == 0) {
                root[find(pw)] = -1;
                parent[find(pw)] = q;
                name[find(pw)] = q;
                return q;
            }
        }
        if (root[q] == -1 && name[q] != -1) {
            int qw = name[q];
            if (size[find(qw)] == 0) {
                root[find(qw)] = -1;
                parent[find(qw)] = p;
                name[find(qw)] = p;
                return p;
            }
        }
        if (name[p] != -1) p = find(name[p]);
        if (name[q] != -1) q = find(name[q]);
        if ((info[p]->get_r_amount() == 0) && (info[q]->get_r_amount() == 0)) {
            if (p > q) {
                size[p] = 0;
                root[q] = -1;
                root[p] = p;
                parent[q] = p;
                name[q] = p;
                return p;
            } else {
                size[q] = 0;
                root[p] = -1;
                root[q] = q;
                parent[p] = q;
                name[p] = q;
                return q;
            }
        }
        if (info[p]->get_r_amount() == 0) {
            root[q] = q;
            root[p] = -1;
            parent[p] = q;
            name[p] = q;
            return q;
        }
        if (info[q]->get_r_amount() == 0) {
            root[q] = -1;
            root[p] = p;
            parent[q] = p;
            name[q] = p;
            return p;
        }
        int bigger = (size[root[p]] > size[root[q]]) ? p : q;
        int smaller = (size[root[p]] > size[root[q]]) ? q : p;
        size[root[bigger]] += size[root[smaller]];
        parent[root[smaller]] = root[bigger];

        name[root[bigger]] = p;
        name[root[smaller]] = -1;
        root[p] = root[bigger];
        root[q] = -1;

        return p;
    }

    void print()
    {
        cout << "new:--------------------------------------------" << endl;
        for (int i = 0; i < n; i++) {
            cout << "key: " << i << ",		group: " << find(i) << endl;
        }
        cout << "by group:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "group " << i << "| root: " << root[i] << "	ptr: " << info[i] << endl;
        }
    }
};

#endif // HW2DATASTRUCTURE_UNIONFIND_H
