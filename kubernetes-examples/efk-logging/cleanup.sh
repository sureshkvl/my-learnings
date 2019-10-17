#kubectl create namespace logging
kubectl delete -f elastic.yaml -n logging
kubectl delete -f kibana.yaml -n logging
kubectl delete -f fluentd-daemonset-elasticsearch-rbac.yaml
