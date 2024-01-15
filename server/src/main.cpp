#include <grpc++/server_builder.h>

#include <proto/protos/calculator.grpc.pb.h>

using std::string;
using std::unique_ptr;
using std::cout;
using std::endl;

constexpr int64_t SUMMAND_MAX = INT64_MAX / 2;
constexpr int64_t SUMMAND_MIN = INT64_MIN / 2;

constexpr int64_t FACTOR_MAX = static_cast<int64_t>(std::floor(std::sqrt(INT64_MAX)));
constexpr int64_t FACTOR_MIN = -static_cast<int64_t>(std::floor(std::sqrt(INT64_MAX)));

class CalculatorServiceImpl final : public Calculator::Service {
    grpc::Status Calculate(grpc::ServerContext* context, const Request* request, Result* response) {
        if (request->operation() == add) {
            if (request->num1() > SUMMAND_MAX || request->num2() > SUMMAND_MAX || request->num1() < SUMMAND_MIN
                || request->num2() < SUMMAND_MIN) {
                return grpc::Status::CANCELLED;
                }
            response->set_value(request->num1() + request->num2());
        } else if (request->operation() == multiply) {
            if (request->num1() > FACTOR_MAX || request->num2() > FACTOR_MAX || request->num1() < FACTOR_MIN
                || request->num2() < FACTOR_MIN) {
                return grpc::Status::CANCELLED;
                }
            response->set_value(request->num1() * request->num2());
        }

        return grpc::Status::OK;
    }
};

int main(int argc, char* argv[]) {
    string server_address = "0.0.0.0:50000";
    CalculatorServiceImpl calculator_service;

    grpc::ServerBuilder server_builder;
    server_builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    server_builder.RegisterService(&calculator_service);
    unique_ptr<grpc::Server> server(server_builder.BuildAndStart());

    cout << "Server listening on " << server_address << "..." << endl;

    return 0;
}
