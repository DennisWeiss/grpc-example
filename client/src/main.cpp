#include <iostream>
#include <grpc++/create_channel.h>
#include <proto/protos/calculator.grpc.pb.h>

#include "Operation.h"

using std::cout;
using std::endl;
using std::unique_ptr;
using std::shared_ptr;


class CalculatorClient {
private:
    unique_ptr<Calculator::Stub> _stub;

public:
    CalculatorClient(const shared_ptr<grpc::Channel>& channel) : _stub(Calculator::NewStub(channel)) {}

    int64_t RequestCalc(grpcexampleclient::Operation operation, int64_t a, int64_t b) {
        Request request;
        request.set_operation(MapOperation(operation));
        request.set_num1(a);
        request.set_num2(b);

        Result result;

        grpc::ClientContext client_context;

        grpc::Status status = _stub->Calculate(&client_context, request, &result);

        if (status.ok()) {
            return result.value();
        }
        return -1;
    }

private:
    Operation MapOperation(grpcexampleclient::Operation operation) {
        if (operation == grpcexampleclient::ADD) {
            return add;
        }
        if (operation == grpcexampleclient::MULTIPLY) {
            return multiply;
        }
        return add;
    }
};

int main(int agrc, char* argv[]) {
    CalculatorClient calculator_client(CreateChannel("localhost:50000", grpc::InsecureChannelCredentials()));

    std::string operation_str;
    std::cin >> operation_str;

    grpcexampleclient::Operation operation;

    if (operation_str == "add") {
        operation = grpcexampleclient::ADD;
    } else if (operation_str == "mul") {
        operation = grpcexampleclient::MULTIPLY;
    } else {
        std::cerr << "Valid operation are 'add' and 'mul'";
        return 1;
    }

    int64_t a, b;

    std::cin >> a;
    std::cin >> b;

    int64_t result = calculator_client.RequestCalc(operation, a, b);

    std::cout << "Result is " << std::to_string(result) << endl;

    return 0;
}
