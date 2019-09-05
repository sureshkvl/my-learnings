### Procedure:

kubectl apply -f redis-master-deployment.yaml
kubectl apply -f redis-master-service.yaml
kubectl apply -f redis-slave-deployment.yaml
kubectl apply -f redis-slave-service.yaml
kubectl apply -f frontend-deployment.yaml
kubectl apply -f frontend-service.yaml


Access the Frontend URL

http://node-ip:31323

### Ref:

https://kubernetes.io/docs/tutorials/stateless-application/guestbook/
