import pandas as pd
import sklearn
import numpy as np

drivers = pd.read_csv('./drivertrain.csv')

features = drivers[['Distance', 'Force']]
sleep = drivers[['Sleep']]

from sklearn.model_selection import train_test_split

train_features, test_features, train_labels, test_labels = train_test_split(features, sleep)
                                                                        
from sklearn.preprocessing import StandardScaler

scaler = StandardScaler()  
  
train_features = scaler.fit_transform(train_features)

test_features = scaler.transform(test_features)

from sklearn.linear_model import LogisticRegression

model = LogisticRegression()

model.fit(train_features, train_labels)

##print(model.score(train_features, train_labels))
##print(model.score(test_features, test_labels))
##print(model.coef_)

Jack = np.array([130.0, 5.0])
Rose = np.array([95.0, 304.0])  
ME = np.array([140.0, 2.0])

sample_drivers = np.array([Jack, Rose, ME])

sample_drivers = scaler.transform(sample_drivers) # scaling해주는 작업.

print(model.predict(sample_drivers))  
  
print(model.predict_proba(sample_drivers))
