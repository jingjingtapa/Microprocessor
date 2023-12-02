import pandas as pd
import sklearn
import numpy as np

passengers = pd.read_csv('./train.csv')
passengers['Sex']=passengers['Sex'].map({'female':1,'male':0})

dummies = pd.get_dummies(passengers['Pclass'])
del passengers['Pclass']
passengers = pd.concat([passengers,dummies], axis = 1, join = 'inner')
passengers.rename(columns = {1:'FirstClass', 2:'SecondClass', 3:'EtcClass'}, inplace =True)
features = passengers[['Sex', 'Age', 'FirstClass', 'SecondClass']]
survival = passengers[['Survived']]

from sklearn.model_selection import train_test_split

train_features, test_features, train_labels, test_labels = train_test_split(features, survival)

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

Jack = np.array([0.0, 20.0, 0.0, 0.0])  
Rose = np.array([1.0, 17.0, 1.0, 0.0])  
ME = np.array([0.0, 32.0, 1.0, 0.0])

sample_passengers = np.array([Jack, Rose, ME])

sample_passengers = scaler.transform(sample_passengers)

print(model.predict(sample_passengers))  
  
print(model.predict_proba(sample_passengers))
