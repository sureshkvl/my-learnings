kubectl create namespace logging
kubectl create -f elastic.yaml -n logging
kubectl create -f kibana.yaml -n logging
kubectl creaet -f fluentd-daemonset-elasticsearch-rbac
kubectl get pods -n logging
kubectl get svc -n logging