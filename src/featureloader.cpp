
#include "featureloader.h"

#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

bool feature_loader::loadsamplefiles(const char* filename) {

  ifstream in(filename);

  if(!in) {
    cout << "Cannot open file.\n";
    return false;
  }

  while (!in.eof()) {

    std::string sample_id;
 
    in >> sample_id;
    samples[sample_id] = 1;
  }

  in.close();


  return true;



}


bool feature_loader::loadfilterfiles(const char* filename) {

  ifstream in(filename); // input

  if(!in) {
    cout << "Cannot open file.\n";
    return false;
  }

  while (!in.eof()) {

//    char* filter_id = new char[20];
    std::string filter_id;
 
    in >> filter_id;
    filters[filter_id] = 1;
  }

  in.close();

/*  
  map<std::string, int>::iterator it;

  for (it = filters.begin(); it != filters.end(); it++ )
    std::cout << (*it).first << " => " << (*it).second << std::endl;
*/

  return true;



}

bool feature_loader::loadfromfile(const char* fileName, int length){

  ifstream in(fileName); // input

  if(!in) {
    cout << "Cannot open file.\n";
    return false;
  }

  //cout << "file opened." << endl;

  char imagename[1000];
  char comment;
  float feature[length];

  feature_item featureitem(length);

  while (!in.eof()) {

    for (int i = 0; i < length; i++) {
      in >> feature[i];
    }
    in >> comment;
    in >> imagename;

    if (filters.size() > 0) {
      if (filters.find(imagename) != filters.end()) {
        feature_item* featureitem = new feature_item(length);

        featureitem->load_id(imagename);
        featureitem->load_feature(feature, length);
        if (samples.size() > 0 && (samples.find(imagename) != samples.end())) {
          sample_feature_list.push_back(*featureitem);
        }
        else {
          feature_list.push_back(*featureitem);  
        }
        delete featureitem;
      }

/*
      map<std::string, int>::iterator it;
 
      for (it = filters.begin(); it != filters.end(); it++ ) {
        if (strcmp(imagename, (*it).first) == 0) {

          //std::cout << "in domain: " << imagename << std::endl;
          featureitem.load_id(imagename);
          featureitem.load_feature(feature, length);
          feature_list.push_back(featureitem);  
   
        }     
      }
*/
    }
    else {
      feature_item* featureitem = new feature_item(length);

      featureitem->load_id(imagename);
      featureitem->load_feature(feature, length);

      if (samples.size() > 0 && (samples.find(imagename) != samples.end())) {
        sample_feature_list.push_back(*featureitem);
      }
      else {
        feature_list.push_back(*featureitem);  
      }
      //  feature_list.push_back(*featureitem);  

      delete featureitem;
    }

  }

  //cout << *feature_list[0].feature << endl;

  in.close();
  return true;

}

feature_loader::feature_loader(){
}

feature_loader::~feature_loader(){
}

