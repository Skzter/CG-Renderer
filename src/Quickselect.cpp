#include "../include/Quickselect.hpp"

// Standard partition process of QuickSort.
    // It considers the last element as pivot
    // and moves all smaller elements to the left of
    // it and greater elements to the right.
    int Quickselect::partitionDir(std::vector<Face3D*> arr, int l, int r, size_t dir) {
        Face3D* pivot = arr.at(r);
        int i = l;
        for (int j = l; j <= r - 1; j++) {
            
            if (Face3D::smallerEqDir(arr.at(j), pivot,dir)) {
                std::swap(arr.at(i), arr.at(j));
                i++;
            }
        }
        std::swap(arr.at(i), arr.at(r));
        return i;
    }

    // This function returns the k-th smallest 
    // element in arr[l..r] using QuickSort-based method.
    // ASSUMPTION: ALL ELEMENTS IN ARR[] ARE DISTINCT.
    Vector3D Quickselect::kthSmallestDir(std::vector<Face3D*>& arr, int l, int r, int k, size_t dir) {
    
        // If k is smaller than the number of elements
        // in the array.
    if (k > 0 && k <= r - l + 1) {

            // Partition the array around the last 
            // element and get the position of the pivot 
            // element in the sorted array.
            int index = partitionDir(arr, l, r, dir);

            // If position is the same as k.
            if (index - l == k - 1){
                //std::cout << "Index: " << index << std::endl;
                std::cout << *arr.at(index) << std::endl;
                return arr.at(index)->middlePoint();
            }

            // If position is more, recur for the left subarray.
            if (index - l > k - 1){
                //std::cout << "smaller!" << std::endl;
                return kthSmallestDir(arr, l, index - 1, k, dir);
            }
            // Else recur for the right subarray.
            //std::cout << "bigger!" << std::endl;
            return kthSmallestDir(arr, index + 1, r, 
                                k - index + l - 1, dir);
        }

        // If k is more than the number of elements in the array.
        std::cout << "max!" << std::endl;
        return Vector3D(std::numeric_limits<float>::max(),std::numeric_limits<float>::max(),std::numeric_limits<float>::max());
    }