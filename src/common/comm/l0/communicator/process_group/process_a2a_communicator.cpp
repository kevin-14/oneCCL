/*
 Copyright 2016-2020 Intel Corporation
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
     http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "ccl.hpp"
#include "ccl_type_traits.hpp"
#include "common/comm/l0/communicator/process_group/process_a2a_communicator_impl.hpp"
#include "common/comm/l0/gpu_comm_attr.hpp"
#include "common/comm/l0/context/process_group_ctx.hpp"

using namespace ccl;

process_a2a_communicator::process_a2a_communicator(ccl::unified_device_type&& device,
                                                   size_t thread_idx,
                                                   size_t process_idx,
                                                   const ccl::device_comm_attr_t& attr)
        : base_t(std::move(device), thread_idx, process_idx, /*comm_attr, */ attr) {}

void process_a2a_communicator::visit(ccl::gpu_comm_attr& comm_attr) {
    ctx = comm_attr.get_process_context();

    //get rank & size
    auto topology = ctx->get_process_topology<base_t::topology_class()>(process_id, thread_id);
    this->initialize_comm_addr(get_device_path(), topology);
}

void process_a2a_communicator::barrier(ccl::stream::impl_t& stream) {
    throw ccl::ccl_error(std::string(__PRETTY_FUNCTION__) + " - is not implemented yet");
}

/* allgatherv */
ccl::communicator::coll_request_t process_a2a_communicator::allgatherv_impl(
    const void* send_buf,
    size_t send_count,
    void* recv_buf,
    const size_t* recv_counts,
    ccl_datatype_t dtype,
    const ccl::coll_attr* attr,
    ccl::stream::impl_t& stream) {
    throw ccl::ccl_error(std::string(__PRETTY_FUNCTION__) + " - is not implemented");
    return {};
}

/* allreduce */
ccl::communicator::coll_request_t process_a2a_communicator::allreduce_impl(
    const void* send_buf,
    void* recv_buf,
    size_t count,
    ccl_datatype_t dtype,
    ccl::reduction reduction,
    const ccl::coll_attr* attr,
    ccl::stream::impl_t& stream) {
    throw ccl::ccl_error(std::string(__PRETTY_FUNCTION__) + " - is not implemented");
    return {};
}

/* alltoall */
ccl::communicator::coll_request_t process_a2a_communicator::alltoall_impl(
    const void* send_buf,
    void* recv_buf,
    size_t count,
    ccl_datatype_t dtype,
    const ccl::coll_attr* attr,
    ccl::stream::impl_t& stream) {
    throw ccl::ccl_error(std::string(__PRETTY_FUNCTION__) + " - is not implemented");
    return {};
}

/* alltoallv */
ccl::communicator::coll_request_t process_a2a_communicator::alltoallv_impl(
    const void* send_buf,
    const size_t* send_counts,
    void* recv_buf,
    const size_t* recv_counts,
    ccl_datatype_t dtype,
    const ccl::coll_attr* attr,
    ccl::stream::impl_t& stream) {
    throw ccl::ccl_error(std::string(__PRETTY_FUNCTION__) + " - is not implemented");
    return {};
}

/* bcast */
ccl::communicator::coll_request_t process_a2a_communicator::bcast_impl(
    void* buf,
    size_t count,
    ccl_datatype_t dtype,
    size_t root,
    const ccl::coll_attr* attr,
    ccl::stream::impl_t& stream) {
    throw ccl::ccl_error(std::string(__PRETTY_FUNCTION__) + " - is not implemented");
    return {};
}

/* reduce */
ccl::communicator::coll_request_t process_a2a_communicator::reduce_impl(
    const void* send_buf,
    void* recv_buf,
    size_t count,
    ccl_datatype_t dtype,
    ccl::reduction reduction,
    size_t root,
    const ccl::coll_attr* attr,
    ccl::stream::impl_t& stream) {
    throw ccl::ccl_error(std::string(__PRETTY_FUNCTION__) + " - is not implemented");
    return {};
}

/* sparse_allreduce */
ccl::communicator::coll_request_t process_a2a_communicator::sparse_allreduce_impl(
    const void* send_ind_buf,
    size_t send_ind_count,
    const void* send_val_buf,
    size_t send_val_count,
    void* recv_ind_buf,
    size_t recv_ind_count,
    void* recv_val_buf,
    size_t recv_val_count,
    ccl_datatype_t index_dtype,
    ccl_datatype_t value_dtype,
    ccl::reduction reduction,
    const ccl::coll_attr* attr,
    ccl::stream::impl_t& stream) {
    throw ccl::ccl_error(std::string(__PRETTY_FUNCTION__) + " - is not implemented");
    return {};
}

COMM_INTERFACE_COLL_INSTANTIATIONS(process_a2a_communicator, char);
COMM_INTERFACE_COLL_INSTANTIATIONS(process_a2a_communicator, int);
COMM_INTERFACE_COLL_INSTANTIATIONS(process_a2a_communicator, int64_t);
COMM_INTERFACE_COLL_INSTANTIATIONS(process_a2a_communicator, uint64_t);
COMM_INTERFACE_COLL_INSTANTIATIONS(process_a2a_communicator, float);
COMM_INTERFACE_COLL_INSTANTIATIONS(process_a2a_communicator, double);

#ifdef CCL_ENABLE_SYCL
COMM_INTERFACE_COLL_CLASS_INSTANTIATIONS(process_a2a_communicator, cl::sycl::buffer<char COMMA 1>);
COMM_INTERFACE_COLL_CLASS_INSTANTIATIONS(process_a2a_communicator, cl::sycl::buffer<int COMMA 1>);
COMM_INTERFACE_COLL_CLASS_INSTANTIATIONS(process_a2a_communicator,
                                         cl::sycl::buffer<int64_t COMMA 1>);
COMM_INTERFACE_COLL_CLASS_INSTANTIATIONS(process_a2a_communicator,
                                         cl::sycl::buffer<uint64_t COMMA 1>);
COMM_INTERFACE_COLL_CLASS_INSTANTIATIONS(process_a2a_communicator, cl::sycl::buffer<float COMMA 1>);
COMM_INTERFACE_COLL_CLASS_INSTANTIATIONS(process_a2a_communicator,
                                         cl::sycl::buffer<double COMMA 1>);
#endif //CCL_ENABLE_SYCL

COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, char, char);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, char, int);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, char, ccl::bfp16);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, char, float);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, char, double);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, char, int64_t);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, char, uint64_t);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int, char);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int, int);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int, ccl::bfp16);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int, float);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int, double);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int, int64_t);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int, uint64_t);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int64_t, char);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int64_t, int);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator,
                                                       int64_t,
                                                       ccl::bfp16);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int64_t, float);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int64_t, double);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int64_t, int64_t);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, int64_t, uint64_t);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, uint64_t, char);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, uint64_t, int);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator,
                                                       uint64_t,
                                                       ccl::bfp16);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, uint64_t, float);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, uint64_t, double);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator, uint64_t, int64_t);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_INSTANTIATION(process_a2a_communicator,
                                                       uint64_t,
                                                       uint64_t);

#ifdef CCL_ENABLE_SYCL
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_CLASS_INSTANTIATION(process_a2a_communicator,
                                                             cl::sycl::buffer<int COMMA 1>,
                                                             cl::sycl::buffer<float COMMA 1>);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_CLASS_INSTANTIATION(process_a2a_communicator,
                                                             cl::sycl::buffer<int COMMA 1>,
                                                             cl::sycl::buffer<ccl::bfp16 COMMA 1>);

COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_CLASS_INSTANTIATION(process_a2a_communicator,
                                                             cl::sycl::buffer<int64_t COMMA 1>,
                                                             cl::sycl::buffer<float COMMA 1>);
COMM_INTERFACE_SPARSE_ALLREDUCE_EXPLICIT_CLASS_INSTANTIATION(process_a2a_communicator,
                                                             cl::sycl::buffer<int64_t COMMA 1>,
                                                             cl::sycl::buffer<ccl::bfp16 COMMA 1>);
#endif //CCL_ENABLE_SYCL
