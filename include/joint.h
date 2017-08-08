#ifndef JOINT_H
#define JOINT_H

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

namespace bvh {

class Joint {
  public:
    /**
     *  A struct that keep offset of joint in relation to parent
     */
    struct Offset {
      float x;
      float y;
      float z;
    };

    /**
     * A enumeration type useful for set order of channels for every joint
     */
    enum class Channel {
      XPOSITION,
      YPOSITION,
      ZPOSITION,
      ZROTATION,
      XROTATION,
      YROTATION
    };

    /**
     * A string names for each channel
     */
    const std::vector<std::string> channel_name_str = {
      "XPOSITION",
      "YPOSITION",
      "ZPOSITION",
      "ZROTATION",
      "XROTATION",
      "YROTATION"
    };

    void add_frame_motion_data(const std::vector <float>& data) {
      channel_data_.push_back(data);
    }

    std::shared_ptr <Joint> parent() const { return parent_; }

    std::string name() const { return name_; }

    Offset offset() const { return offset_; }

    std::vector <Channel> channels_order() const {
      return channels_order_;
    }

    std::vector <std::shared_ptr <Joint>> children() const {
      return children_;
    }

    const std::vector <std::vector <float>>& channel_data() const {
      return channel_data_;
    }

    const std::vector <float>& channel_data(unsigned frame) const {
      return channel_data_[frame];
    }

    float channel_data(unsigned frame, unsigned channel_num) const {
      return channel_data_[frame][channel_num];
    }

    const std::vector <glm::mat4>& matrix() const {
      return ltm_;
    }

    glm::mat4 matrix(unsigned frame) const {
      return ltm_[frame];
    }

    std::vector <glm::mat4> ltm() const {
      return ltm_;
    }

    glm::mat4 ltm(unsigned frame) const {
      return ltm_[frame];
    }

    std::vector <glm::vec3> pos() const {
      return pos_;
    }

    glm::vec3 pos(unsigned frame) const {
      return pos_[frame];
    }

    unsigned num_channels() const { return channels_order_.size(); }

    void set_parent(const std::shared_ptr <Joint> arg) { parent_ = arg; }

    void set_name(const std::string arg) { name_ = arg; }

    void set_offset(const Offset arg) { offset_ = arg; }

    void set_channels_order(const std::vector <Channel>& arg) {
      channels_order_ = arg;
    }

    void set_children(const std::vector <std::shared_ptr <Joint>>& arg) {
      children_ = arg;
    }

    void set_channel_data(const std::vector <std::vector <float>>& arg) {
      channel_data_ = arg;
    }

    /*! \brief Sets local transformation matrix for selected frame
     *  @param  matrix  The local transformation matrix to be set
     *  @param  frame   The number of frame for which you want set ltm. As
                        default it is set to 0.
     */
    void set_ltm(const glm::mat4 matrix, unsigned frame = 0) {
      if (frame > 0 && frame < ltm_.size())
        ltm_[frame] = matrix;
      else
        ltm_.push_back(matrix);
    }

    /*! \brief Sets local transformation matrix for selected frame
     *  @param  pos     The position of joint in selected frame to be set
     *  @param  frame   The number of frame for which you want set position. As
                        default it is set to 0.
     */
    void set_pos(const glm::vec3 pos, unsigned frame = 0) {
      if (frame > 0 && frame < pos_.size())
        pos_[frame] = pos;
      else
        pos_.push_back(pos);
    }

    /*! \brief Get vector of channels name
     *  @return vector of names
     */
    const std::vector<std::string> get_channels_name() const {
      std::vector<std::string> channel_names;

      for (int i = 0; i < channels_order_.size(); i++)
        channel_names.push_back(channel_name_str[static_cast<int>(
            channels_order_[i])]);

      return channel_names;
    }

  private:
    /** Parent joint in file hierarchy */
    std::shared_ptr <Joint> parent_;
    std::string name_;
    Offset offset_;
    /** Order of joint's input channels */
    std::vector <Channel> channels_order_;
    /** Pointers to joints that are children of this in hierarchy */
    std::vector <std::shared_ptr <Joint>> children_;
    /** Structure for keep joint's channel's data.
     *  Each vector keep data for one channel.
     */
    std::vector <std::vector <float> > channel_data_;
    /** Local transformation matrix for each frame */
    std::vector <glm::mat4> ltm_;
    /** Vector x, y, z of joint position for each frame */
    std::vector <glm::vec3> pos_;
};

} // namespace
#endif // JOINT_H
