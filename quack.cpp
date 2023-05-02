/**
 * @file quack.cpp
 * Implementation of the Quack class.
 * 
 *
 */
/* Constructor, initializes member variables appropriately. */
template <class T>
Quack<T>::Quack() {
    n1 = 0;
    n2 = -1;
}

/**
 * Adds the parameter object to the right of the Quack.
 *
 * @param newItem object to be added to the Quack.
 */

 
template <class T>
void Quack<T>::pushR(T newItem) {
    n2++;
    data.push_back(newItem);
}

/**
 * Removes the object at the left of the Quack, and returns it to the
 * caller.
 *
 * See .h file for implementation notes.
 *
 * @return The item that used to be at the left of the Quack.
 */
template <class T>
T Quack<T>::popL() {
    T poped = peekL();
    
    n1++;
    if(isEmpty()){
        n1 = 0;
        n2 = -1;
        data.resize(0);
        return poped;
    } else if(n2 - n1 + 1 <= n1){
        vector<T> temp;
        for (int i=n1;i<=n2;i++){
            temp.push_back(data[i]);
        }
        data.resize(temp.size());
        for (unsigned int i=0;i<temp.size();i++){
            data[i] = temp[i];
        }
        n1 = 0;
        n2 = temp.size() - 1;
    }
    return poped;
   
}
/**
 * Removes the object at the right of the Quack, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Quack.
 */
template <class T>
T Quack<T>::popR() {
    T poped = peekR();
    data.pop_back();
    n2--;
    
    if (n2-n1+1<=n1){
        vector<T> temp;
        for (int i=n1;i<=n2;i++){
            temp.push_back(data[i]);
        }
        data.resize(temp.size());
        for (unsigned int i=0;i<temp.size();i++){
            data[i] = temp[i];
        }
        n1 = 0;
        n2 = temp.size() - 1;
    }
    return poped;

}

/**
 * Finds the object at the left of the Quack, and returns it to the
 * caller. Unlike popL(), this operation does not alter the quack.
 *
 * @return The item at the front of the quack.
 */
template <class T>
T Quack<T>::peekL() {
    return data[n1];
   
}

/**
 * Finds the object at the right of the Quack, and returns it to the
 * caller. Unlike popR(), this operation does not alter the quack.
 *
 * @return the value of The item at the right of the quack.
 */
template <class T>
T Quack<T>::peekR() {
    
    return data[n2];
}

/**
 * Determines if the Quack is empty.
 *
 * @return bool which is true if the Quack is empty, false otherwise.
 */
template <class T>
bool Quack<T>::isEmpty() const {
    return n2<n1;

}
